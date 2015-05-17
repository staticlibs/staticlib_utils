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

#include <iostream>
#include <thread>
#include <atomic>
#include <iostream>
#include <cassert>

#include "staticlib/utils/signal_utils.hpp"

namespace su = staticlib::utils;

int main() {
    std::atomic_flag flag = ATOMIC_FLAG_INIT;
    su::initialize_signals();
    su::register_signal_listener([&flag]{
        flag.test_and_set();
    });
    auto th = std::thread{[] {
        std::this_thread::sleep_for(std::chrono::seconds{1});
        su::fire_signal();
    }};
    th.detach();
    su::wait_for_signal();
    std::cout << "signal_utils_test: reached" << std::endl;
    assert(flag.test_and_set());
    
    return 0;
}

