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

#include <functional>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>

#include <signal.h>

#include "staticlib/utils/config.hpp"
#ifdef STATICLIB_WINDOWS
#include <windows.h>
#endif // STATICLIB_WINDOWS

#include "staticlib/utils/UtilsException.hpp"
#include "staticlib/utils/signal_utils.hpp"

namespace staticlib {
namespace utils {

namespace { // anonymous

std::vector<std::function<void(void)>>& get_static_liteners() {
    static std::vector<std::function<void(void)>> vec{};
    return vec;
}

std::mutex& get_static_mutex() {
    static std::mutex mutex{};
    return mutex;
}

std::condition_variable& get_static_cv() {
    static std::condition_variable cv{};
    return cv;
}

bool& get_static_initialized() {
    static bool initialized = false;
    return initialized;
}

bool& get_static_fired() {
    static bool fired = false;
    return fired;
}

void handler_internal() {
    for (std::function<void(void)> fu : get_static_liteners()) {
        fu();
    }
    bool& fired = get_static_fired();
    fired = true;
    get_static_cv().notify_all();
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
    SetConsoleCtrlHandler(handler_platform, TRUE);
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
    std::lock_guard<std::mutex> guard{get_static_mutex()};
    bool& si = get_static_initialized();
    if (si) throw UtilsException("Signal listeners double initialization error");
    initialize_signals_platform();
    si = true;
}

void register_signal_listener(std::function<void(void)> listener) {
    std::lock_guard<std::mutex> guard{get_static_mutex()};
    get_static_liteners().emplace_back(std::move(listener));
}

void wait_for_signal() {
    std::unique_lock<std::mutex> lock{get_static_mutex()};
    bool& fired = get_static_fired();
    fired = false;
    get_static_cv().wait(lock, get_static_fired);
}

void fire_signal() {
    std::lock_guard<std::mutex> guard{get_static_mutex()};
    handler_internal();
}

} // namespace
}

