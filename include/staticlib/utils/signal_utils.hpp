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
 * File:   signal_utils.hpp
 * Author: alex
 *
 * Created on March 12, 2015, 8:21 PM
 */

#ifndef STATICLIB_UTILS_SIGNAL_UTILS_HPP
#define STATICLIB_UTILS_SIGNAL_UTILS_HPP

#include <condition_variable>
#include <functional>
#include <memory>
#include <mutex>
#include <thread>
#include <vector>

#include "staticlib/utils/utils_exception.hpp"

namespace staticlib {
namespace utils {


class signal_ctx {
    friend void initialize_signals(signal_ctx& ctx);
    friend void register_signal_listener(signal_ctx& ctx, std::function<void(void)> listener);
    friend void wait_for_signal(signal_ctx& ctx);
    friend void fire_signal(signal_ctx& ctx);
    friend void signal_fired(signal_ctx& ctx);
    friend void on_destroy(signal_ctx& ctx);

    enum class signal_state { not_initialized, initialized, fired };

    std::mutex mtx;
    std::condition_variable cv;
    signal_state state = signal_state::not_initialized;
    std::vector<std::function<void(void)>> listeners;
    std::unique_ptr<std::thread> th;

    signal_ctx(const signal_ctx&) = delete;
    void operator=(const signal_ctx&) = delete;

public:
    signal_ctx() :
    state(signal_state::not_initialized) {};

    ~signal_ctx() STATICLIB_NOEXCEPT {
        on_destroy(*this);
    }
};

/**
 * Initializes signal handlers to be used with 'wait_for_signal'.
 * Should be called only once.
 */
void initialize_signals(signal_ctx& ctx);

/**
 * Registers listener for SIGINT/SIGTERM
 * (or CTRL_C_EVENT/CTRL_BREAK_EVENT/CTRL_CLOSE_EVENT/CTRL_SHUTDOWN_EVENT on Windows)
 * 
 * @param listener listener function (lambda)
 */
void register_signal_listener(signal_ctx& ctx, std::function<void(void)> listener);

/*
 * Blocks current thread until the SIGINT/SIGTERM
 * signal will be received by this process.
 */
void wait_for_signal(signal_ctx& ctx);

/**
 * Emulates receiving SIGINT/SIGTERM for this process
 */
void fire_signal(signal_ctx& ctx);

} // namespace
}

#endif /* STATICLIB_UTILS_SIGNAL_UTILS_HPP */

