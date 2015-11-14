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

#include <cstring>
#include <iostream>

#include "staticlib/utils/assert.hpp"

#include "staticlib/utils/UtilsException.hpp"
#include "staticlib/utils/string_utils.hpp"

namespace ss = staticlib::utils;

void test_to_string() {
    slassert("42" == ss::to_string(42));
    slassert("42" == ss::to_string(std::string("42")));
}

class BadExternalClass {
    friend std::ostream &operator<<(std::ostream&, const BadExternalClass&) {
        throw std::exception();
    }
};

void test_to_string_exception() {
    bool catched = false;
    try {
        BadExternalClass bc{};
        ss::to_string(bc);        
    } catch(const ss::UtilsException&) {
        catched = true;
    }
    slassert(catched);
}

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

int main() {
    try {
        test_to_string();
        test_to_string_exception();
        test_get_buffer_char();
        test_get_buffer_wchar();
        test_get_buffer_exception();
        test_alloc_copy();
        test_split();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}

