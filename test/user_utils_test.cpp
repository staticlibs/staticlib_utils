/*
 * Copyright 2019, alex at staticlibs.net
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
 * File:   user_utils_test.cpp
 * Author: alex
 *
 * Created on April 4, 2019, 7:31 PM
 */
#include "staticlib/utils/user_utils.hpp"

#include <cstring>
#include <iostream>

#include "staticlib/config/assert.hpp"

void test_user_name() {
    auto name = sl::utils::user_name();
    slassert(name.length() > 0);
}

void test_user_home_dir() {
    auto dir = sl::utils::user_home_dir();
    slassert(dir.length() > 0);
}

void test_user_localappdata_dir() {
    auto dir = sl::utils::user_localappdata_dir();
    slassert(dir.length() > 0);
}

int main() {
    try {
        test_user_name();
        test_user_home_dir();
        test_user_localappdata_dir();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}
