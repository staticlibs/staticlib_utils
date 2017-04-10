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
 * File:   signal_utils_test.cpp
 * Author: alex
 *
 * Created on March 12, 2015, 9:38 PM
 */

#include "staticlib/utils/signal_utils.hpp"

#include <atomic>
#include <iostream>
#include <thread>

#include "staticlib/config/assert.hpp"

void test_signal() {
    std::atomic_flag flag = ATOMIC_FLAG_INIT;
    sl::utils::initialize_signals();
    sl::utils::register_signal_listener([&flag] {
        flag.test_and_set();
    });
    auto th = std::thread{[] {
            std::this_thread::sleep_for(std::chrono::seconds{1});
            sl::utils::fire_signal();
        }};
    th.detach();
    sl::utils::wait_for_signal();
    std::cout << "signal_utils_test: reached" << std::endl;
    slassert(flag.test_and_set());
}

int main() {
    try {
        test_signal();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}
