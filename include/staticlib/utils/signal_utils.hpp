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

#ifndef STATICLIB_SIGNAL_UTILS_HPP
#define	STATICLIB_SIGNAL_UTILS_HPP

#include <functional>

namespace staticlib {
namespace utils {

/**
 * Initializes signal handlers to be used with 'wait_for_signal'.
 * Should be called only once.
 */
void initialize_signals();

/**
 * Registers listener for SIGINT/SIGTERM
 * (or CTRL_C_EVENT/CTRL_BREAK_EVENT/CTRL_CLOSE_EVENT/CTRL_SHUTDOWN_EVENT on Windows)
 * 
 * @param listener listener function (lambda)
 */
void register_signal_listener(std::function<void(void)> listener);

/*
 * Blocks current thread until the SIGINT/SIGTERM
 * signal will be received by this process.
 */
void wait_for_signal();

/**
 * Emulates receiving SIGINT/SIGTERM for this process
 */
void fire_signal();

} // namespace
}

#endif	/* STATICLIB_SIGNAL_UTILS_HPP */

