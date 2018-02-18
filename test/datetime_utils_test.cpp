/*
 * Copyright 2018, alex at staticlibs.net
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
 * File:   datetime_utils_test.cpp
 * Author: alex
 *
 * Created on February 18, 2018, 1:42 PM
 */

#include "staticlib/utils/datetime_utils.hpp"

#include <chrono>
#include <iostream>
#include <thread>

#include "staticlib/config/assert.hpp"

void test_system() {
    auto start = sl::utils::current_time_millis();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    auto end = sl::utils::current_time_millis();
    slassert(end - start > 50);
}

void test_steady() {
    auto start = sl::utils::current_time_millis_steady();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    auto end = sl::utils::current_time_millis_steady();
    slassert(end - start > 50);
}

int main() {
    try {
        test_system();
        test_steady();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}
