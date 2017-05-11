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
 * File:   url_utils_test.cpp
 * Author: alex
 *
 * Created on May 11, 2017, 10:56 PM
 */

#include "staticlib/utils/url_utils.hpp"

#include <cstring>
#include <iostream>

#include "staticlib/config/assert.hpp"

void test_encode_decode() {
    std::string decoded = R"({"foo": 41, "bar": 42, "baz": 43})";
    std::string encoded = "%7B%22foo%22%3A%2041%2C%20%22bar%22%3A%2042%2C%20%22baz%22%3A%2043%7D";
    slassert(encoded == sl::utils::url_encode(decoded));
    slassert(decoded == sl::utils::url_decode(encoded));
}

int main() {
    try {
        test_encode_decode();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}
