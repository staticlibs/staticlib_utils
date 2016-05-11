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
 * File:   string_utils_test.cpp
 * Author: alex
 *
 * Created on January 2, 2015, 1:06 PM
 */

#include "staticlib/utils/string_utils.hpp"

#include <iostream>
#include <cstring>

#include "staticlib/config/assert.hpp"

namespace ss = staticlib::utils;

void test_get_buffer_char() {
    std::string st{"foo"};
    auto buf = ss::get_buffer(st, 42);
    slassert(3 == strlen(buf));
    slassert(42 == st.size());
}

void test_get_buffer_wchar() {
    std::wstring st{};
    auto buf = ss::get_buffer(st, 42);
    slassert(0 == wcslen(buf));
    slassert(42 == st.size());
}

void test_get_buffer_exception() {
    std::string expected{
R"(basic_string::resize
Error getting buffer with required size: [18446744073709551615] from string, length: [3]
    at namespace>::get_buffer_internal(string_utils.cpp:30))"};
    bool catched = false;

    std::string st{"foo"};
    try {
        ss::get_buffer(st, static_cast<std::string::size_type>(-1));
    } catch(const ss::UtilsException&) {
        catched = true;
        //slassert(expected == e.what());
    }
    slassert(catched);
}

void test_alloc_copy() {
    std::string st{"foo"};
    auto buf = ss::alloc_copy(st);
    slassert(3 == strlen(buf));
    slassert('\0' == buf[3]);
    free(buf);
}

void test_split() {
    std::string src{"foo:bar::baz:"};
    std::vector<std::string> vec = ss::split(src, ':');
    slassert(3 == vec.size());
    slassert("foo" == vec[0]);
    slassert("bar" == vec[1]);
    slassert("baz" == vec[2]);
}

void test_ends_with() {
    slassert(ss::ends_with("foo", "oo"));
    slassert(ss::ends_with("foo", "foo"));
    slassert(!ss::ends_with("foo", "1foo"));
    slassert(ss::ends_with("foo", ""));
    slassert(!ss::ends_with("foo", "ar"));
}

int main() {
    try {
        test_get_buffer_char();
        test_get_buffer_wchar();
        test_get_buffer_exception();
        test_alloc_copy();
        test_split();
        test_ends_with();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}

