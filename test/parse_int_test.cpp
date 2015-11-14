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
 * File:   parse_int_test.cpp
 * Author: alex
 *
 * Created on January 31, 2015, 4:01 PM
 */

#include <cstdlib>
#include <string>
#include <iostream>

#include "staticlib/utils/assert.hpp"

#include "staticlib/utils/parse_int.hpp"

namespace ss = staticlib::utils;

void test_parse_int16() {
    slassert(42 == ss::parse_int16("42"));
    slassert(-42 == ss::parse_int16("-42"));
    bool catched_overflow_big = false;
    try {
        ss::parse_int16("65534");
    } catch (const std::exception&) {
        catched_overflow_big = true;
    }
    slassert(catched_overflow_big);
    bool catched_invalid = false;
    try {
        ss::parse_int16("-4242A");
    } catch (const std::exception&) {
        catched_invalid = true;
    }
    slassert(catched_invalid);
}

void test_parse_uint16() {
    slassert(42 == ss::parse_uint16("42"));
    slassert(65535 == ss::parse_uint16("65535"));
    bool catched_overflow_negative = false;
    try {
        auto parsed = ss::parse_uint16("-42");
        std::cout << parsed << std::endl;
    } catch (const std::exception&) {
        catched_overflow_negative = true;
    }
    slassert(catched_overflow_negative);
    bool catched_overflow_big = false;
    try {
        ss::parse_uint16("65536");
    } catch (const std::exception&) {
        catched_overflow_big = true;
    }
    slassert(catched_overflow_big);
    bool catched_invalid = false;
    try {
        ss::parse_uint16("4242A");
    } catch (const std::exception&) {
        catched_invalid = true;
    }
    slassert(catched_invalid);
}

void test_parse_int32() {
    slassert(42 == ss::parse_int32("42"));
    slassert(-42 == ss::parse_int32("-42"));
    bool catched_overflow_big = false;
    try {
        ss::parse_int32("2147483648");
    } catch (const std::exception&) {
        catched_overflow_big = true;
    }
    slassert(catched_overflow_big);
    bool catched_invalid = false;
    try {
        ss::parse_int32("-4242A");
    } catch (const std::exception&) {
        catched_invalid = true;
    }
    slassert(catched_invalid);
}

void test_parse_uint32() {
    slassert(42 == ss::parse_uint32("42"));
    slassert(4294967295 == ss::parse_uint32("4294967295"));
    bool catched_overflow_negative = false;
    try {
        ss::parse_uint32("-42");
    } catch (const std::exception&) {
        catched_overflow_negative = true;
    }
    slassert(catched_overflow_negative);
    bool catched_overflow_big = false;
    try {
        ss::parse_uint32("4294967296");
    } catch (const std::exception&) {
        catched_overflow_big = true;
    }
    slassert(catched_overflow_big);
    bool catched_invalid = false;
    try {
        ss::parse_uint32("4242A");
    } catch (const std::exception&) {
        catched_invalid = true;
    }
    slassert(catched_invalid);
}

void test_parse_int64() {
    slassert(42 == ss::parse_int64("42"));
    slassert(-42 == ss::parse_int64("-42"));
    bool catched_overflow_big = false;
    try {
        ss::parse_int64("9223372036854775808");
    } catch (const std::exception&) {
        catched_overflow_big = true;
    }
    slassert(catched_overflow_big);
    bool catched_invalid = false;
    try {
        ss::parse_int64("-4242A");
    } catch (const std::exception&) {
        catched_invalid = true;
    }
    slassert(catched_invalid);
}

void test_parse_uint64() {
    slassert(42 == ss::parse_uint64("42"));
    slassert(18446744073709551615u == ss::parse_uint64("18446744073709551615"));
//    bool catched_overflow_negative = false;
//    try {
//        auto parsed = ss::parse_uint64("-42");
//        std::cout << parsed << std::endl;
//    } catch (const std::exception&) {
//        catched_overflow_negative = true;
//    }
//    slassert(catched_overflow_negative);
    bool catched_overflow_big = false;
    try {
        ss::parse_uint64("18446744073709551616");
    } catch (const std::exception&) {
        catched_overflow_big = true;
    }
    slassert(catched_overflow_big);
    bool catched_invalid = false;
    try {
        ss::parse_uint64("4242A");
    } catch (const std::exception&) {
        catched_invalid = true;
    }
    slassert(catched_invalid);
}

int main() {
    try {
        test_parse_int16();
        test_parse_uint16();
        test_parse_int32();
        test_parse_uint32();
        test_parse_int64();
        test_parse_uint64();        
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}
