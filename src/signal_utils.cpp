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

#include <atomic>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <vector>

#include <signal.h>

#include "staticlib/config.hpp"
#ifdef STATICLIB_WINDOWS
#include "staticlib/support/windows.hpp"
#endif // STATICLIB_WINDOWS

namespace staticlib {
namespace utils {

namespace { // anonymous

std::vector<std::function<void(void)>>& static_listeners() {
    static std::vector<std::function<void(void)>> vec{};
    return vec;
}

std::mutex& static_mutex() {
    static std::mutex mutex{};
    return mutex;
}

std::condition_variable& static_cv() {
    static std::condition_variable cv{};
    return cv;
}

bool& static_initialized() {
    static bool initialized = false;
    return initialized;
}

std::atomic<bool>& static_fired() {
    static std::atomic<bool> fired{false};
    return fired;
}

// todo: think about safer handler
// see: https://stackoverflow.com/a/12448113/314015
void handler_internal() {
    for (std::function<void(void)> fu : static_listeners()) {
        fu();
    }
    static_listeners().clear();
    auto& fired = static_fired();
    fired.store(true, std::memory_order_release);
    static_cv().notify_all();
}

#ifdef STATICLIB_WINDOWS

BOOL WINAPI handler_platform(DWORD ctrl_type) {
    switch (ctrl_type) {
    case CTRL_C_EVENT:
    case CTRL_BREAK_EVENT:
    case CTRL_CLOSE_EVENT:
    case CTRL_SHUTDOWN_EVENT:
        handler_internal();
        return TRUE;
    default:
        return FALSE;
    }
}

void initialize_signals_platform() {
    ::SetConsoleCtrlHandler(handler_platform, TRUE);
    // https://stackoverflow.com/a/9719240/314015
    ::SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOGPFAULTERRORBOX);
}

#else // STATICLIB_WINDOWS

void handler_platform(int sig) {
    (void) sig;
    handler_internal();
}

void initialize_signals_platform() {
    signal(SIGINT, handler_platform);
    signal(SIGTERM, handler_platform);
}

#endif // STATICLIB_WINDOWS

} // namespace

void initialize_signals() {
    std::lock_guard<std::mutex> guard{static_mutex()};
    bool& si = static_initialized();
    if (si) {
        throw utils_exception("Signal listeners double initialization error");
    }
    initialize_signals_platform();
    si = true;
}

void register_signal_listener(std::function<void(void)> listener) {
    std::lock_guard<std::mutex> guard{static_mutex()};
    if (!static_initialized()) {
        throw utils_exception("Signal listeners not initialized");
    }
    static_listeners().emplace_back(std::move(listener));
}

// note: not thread-safe, must be used only from main thread
void wait_for_signal() {
    std::unique_lock<std::mutex> lock{static_mutex()};
    if (!static_initialized()) {
        throw utils_exception("Signal listeners not initialized");
    }
    static_fired().store(false, std::memory_order_release);
    static_cv().wait(lock, [] {
        return static_fired().load(std::memory_order_acquire);
    });
}

void fire_signal() {
    std::lock_guard<std::mutex> guard{static_mutex()};
    if (!static_initialized()) {
        throw utils_exception("Signal listeners not initialized");
    }
    handler_internal();
}

} // namespace
}

