/*
 * Copyright 2015, alex at staticlibs.net
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/* 
 * File:   signal_utils.cpp
 * Author: alex
 * 
 * Created on March 12, 2015, 8:49 PM
 */

#include "staticlib/utils/signal_utils.hpp"

#include <cstring>
#include <atomic>
#include <condition_variable>
#include <iostream>
#include <functional>
#include <mutex>
#include <thread>
#include <vector>

#include <signal.h>

#include "staticlib/config.hpp"
#ifdef STATICLIB_WINDOWS
#include "staticlib/support/windows.hpp"
#else // !STATICLIB_WINDOWS
#include <unistd.h>
#endif // STATICLIB_WINDOWS

namespace staticlib {
namespace utils {

namespace { // anonymous

#ifdef STATICLIB_WINDOWS

// global is unavoidable on win
signal_ctx& static_signal_ctx(signal_ctx* ctx_in = nullptr) {
    static signal_ctx* ctx = ctx_in;
    if (nullptr == ctx) {
        auto msg = TRACEMSG("Invalid signals state");
        std::cerr << msg << std::endl;
        throw utils_exception(msg);
    }
    return *ctx;
}

BOOL WINAPI handler_windows(DWORD ctrl_type) {
    switch (ctrl_type) {
    case CTRL_C_EVENT:
    case CTRL_BREAK_EVENT:
    case CTRL_CLOSE_EVENT:
    case CTRL_SHUTDOWN_EVENT:
        signal_fired(static_signal_ctx());
        return TRUE;
    default:
        return FALSE;
    }
}

std::unique_ptr<std::thread> initialize_signals_platform(signal_ctx& ctx) {
    static_signal_ctx(std::addressof(ctx));
    ::SetConsoleCtrlHandler(handler_windows, TRUE);
    return std::unique_ptr<std::thread>();
}

#else // STATICLIB_WINDOWS

void handler_posix(signal_ctx& ctx) {
    // init
    sigset_t mask;
    auto err_empty = sigemptyset(std::addressof(mask));
    if (0 != err_empty) throw utils_exception(TRACEMSG(
            "Error initializing signals handler: [" + ::strerror(err_empty) + "]"));
    auto err_int = sigaddset(std::addressof(mask), SIGINT);
    if (0 != err_int) throw utils_exception(TRACEMSG(
            "Error initializing signals handler: [" + ::strerror(err_int) + "]"));
    auto err_term = sigaddset(std::addressof(mask), SIGTERM);
    if (0 != err_term) throw utils_exception(TRACEMSG(
            "Error initializing signals handler: [" + ::strerror(err_term) + "]"));
    // wait
    int sig = -1;
    auto err_wait = sigwait(std::addressof(mask), std::addressof(sig));
    if (0 != err_wait) throw utils_exception(TRACEMSG(
            "Error waiting for signal: [" + ::strerror(err_wait) + "]"));
    // fire
    signal_fired(ctx);
}

std::unique_ptr<std::thread> initialize_signals_platform(signal_ctx& ctx) {
    sigset_t mask;
    auto err_fill = sigfillset(std::addressof(mask));
    if (0 != err_fill) throw utils_exception(TRACEMSG(
            "Error initializing signals: [" + ::strerror(err_fill) + "]"));
    auto err_mask = sigprocmask(SIG_SETMASK, std::addressof(mask), nullptr);
    if (0 != err_mask) throw utils_exception(TRACEMSG(
            "Error initializing signals: [" + ::strerror(err_mask) + "]"));
    return sl::support::make_unique<std::thread>([&ctx]{
        try {
            handler_posix(ctx);
        } catch(const std::exception& e) {
            std::cerr << "Signal handler worker error:" << std::endl;
            std::cerr << TRACEMSG(e.what()) << std::endl;
        }
    });
}

#endif // STATICLIB_WINDOWS
} // namespace

void initialize_signals(signal_ctx& ctx) {
    std::lock_guard<std::mutex> guard{ctx.mtx};
    if (signal_ctx::signal_state::not_initialized != ctx.state) {
        throw utils_exception("Signal listeners double initialization error");
    }
    ctx.th = initialize_signals_platform(ctx);
    ctx.state = signal_ctx::signal_state::initialized;
}

void register_signal_listener(signal_ctx& ctx, std::function<void(void)> listener) {
    std::lock_guard<std::mutex> guard{ctx.mtx};
    if (signal_ctx::signal_state::initialized != ctx.state) {
        throw utils_exception("Signal listeners not initialized");
    }
    ctx.listeners.emplace_back(std::move(listener));
}

void wait_for_signal(signal_ctx& ctx) {
    std::unique_lock<std::mutex> lock{ctx.mtx};
    if (signal_ctx::signal_state::initialized != ctx.state) {
        throw utils_exception("Signal listeners not initialized");
    }
    ctx.cv.wait(lock, [&ctx] {
        return signal_ctx::signal_state::fired == ctx.state;
    });
}

void fire_signal(signal_ctx& ctx) {
#ifdef STATICLIB_WINDOWS
    signal_fired(ctx);
#else // !STATICLIB_WINDOWS
    (void) ctx;
    kill(getpid(), SIGINT);
#endif // STATICLIB_WINDOWS
}

void on_destroy(signal_ctx& ctx) {
    (void) ctx;
#ifndef STATICLIB_WINDOWS
    std::unique_lock<std::mutex> lock{ctx.mtx};
    if (signal_ctx::signal_state::not_initialized == ctx.state) {
        return;
    }
    if (signal_ctx::signal_state::fired == ctx.state) {
        ctx.th->join();
        return;
    }
    ctx.listeners.clear();
    fire_signal(ctx);
    ctx.cv.wait(lock, [&ctx] {
        return signal_ctx::signal_state::fired == ctx.state;
    });
    ctx.th->join();
#endif // !STATICLIB_WINDOWS
}

void signal_fired(signal_ctx& ctx) {
    std::lock_guard<std::mutex> guard{ctx.mtx};
    if (signal_ctx::signal_state::initialized != ctx.state) {
        return;
    }
    for(auto& fun : ctx.listeners) {
        fun();
    }
    ctx.state = signal_ctx::signal_state::fired;
    ctx.cv.notify_all();
}

} // namespace
}

