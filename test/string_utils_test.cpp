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

#include <cassert>
#include <cstring>
#include <iostream>

#include "staticlib/utils/UtilsException.hpp"
#include "staticlib/utils/string_utils.hpp"

namespace { // anonymous

namespace ss = staticlib::utils;

void test_to_string() {
    assert("42" == ss::to_string(42));
    assert("42" == ss::to_string(std::string("42")));
}

class BadExternalClass {
    friend std::ostream &operator<<(std::ostream& output, const BadExternalClass& bc) {
        (void) bc;
        (void) output;
        throw std::exception();
    }
};

void test_to_string_exception() {
    bool catched = false;
    try {
        BadExternalClass bc{};
        ss::to_string(bc);        
    } catch(const ss::UtilsException& e) {
        (void) e;
        catched = true;
    }
    (void) catched; assert(catched);
}

void test_get_buffer_char() {
    std::string st{"foo"};
    auto buf = ss::get_buffer(st, 42);
    (void) buf;
    assert(3 == strlen(buf));
    assert(42 == st.size());
}

void test_get_buffer_wchar() {
    std::wstring st{};
    auto buf = ss::get_buffer(st, 42);
    (void) buf;
    assert(0 == wcslen(buf));
    assert(42 == st.size());
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
    } catch(const ss::UtilsException& e) {
        (void) e;
        catched = true;
        //assert(expected == e.what());
    }
    (void) catched; assert(catched);
}

void test_alloc_copy() {
    std::string st{"foo"};
    auto buf = ss::alloc_copy(st);
    assert(3 == strlen(buf));
    assert('\0' == buf[3]);
    free(buf);
}

} // namespace


int main() {
    test_to_string();
    test_to_string_exception();
    test_get_buffer_char();
    test_get_buffer_wchar();
    test_get_buffer_exception();
    test_alloc_copy();
    
    return 0;
}

