/* 
 * File:   parse_int_test.cpp
 * Author: alex
 *
 * Created on January 31, 2015, 4:01 PM
 */

#include <cstdlib>
#include <string>
#include <cassert>
#include <iostream>

#include "staticlib/stdlib/parse_int.hpp"

namespace { // anonymous

namespace ss = staticlib::stdlib;

void test_parse_int16() {
    assert(42 == ss::parse_int16("42"));
    assert(-42 == ss::parse_int16("-42"));
    bool catched_overflow_big = false;
    try {
        ss::parse_int16("65534");
    } catch (const std::exception& e) {
        (void) e;
        catched_overflow_big = true;
    }
    assert(catched_overflow_big);
    bool catched_invalid = false;
    try {
        ss::parse_int16("-4242A");
    } catch (const std::exception& e) {
        (void) e;
        catched_invalid = true;
    }
    assert(catched_invalid);
}

void test_parse_uint16() {
    assert(42 == ss::parse_uint16("42"));
    assert(65535 == ss::parse_uint16("65535"));
    bool catched_overflow_negative = false;
    try {
        auto parsed = ss::parse_uint16("-42");
        std::cout << parsed << std::endl;
    } catch (const std::exception& e) {
        (void) e;
        catched_overflow_negative = true;
    }
    assert(catched_overflow_negative);
    bool catched_overflow_big = false;
    try {
        ss::parse_uint16("65536");
    } catch (const std::exception& e) {
        (void) e;
        catched_overflow_big = true;
    }
    assert(catched_overflow_big);
    bool catched_invalid = false;
    try {
        ss::parse_uint16("4242A");
    } catch (const std::exception& e) {
        (void) e;
        catched_invalid = true;
    }
    assert(catched_invalid);
}

void test_parse_int32() {
    assert(42 == ss::parse_int32("42"));
    assert(-42 == ss::parse_int32("-42"));
    bool catched_overflow_big = false;
    try {
        ss::parse_int32("2147483648");
    } catch (const std::exception& e) {
        (void) e;
        catched_overflow_big = true;
    }
    assert(catched_overflow_big);
    bool catched_invalid = false;
    try {
        ss::parse_int32("-4242A");
    } catch (const std::exception& e) {
        (void) e;
        catched_invalid = true;
    }
    assert(catched_invalid);
}

void test_parse_uint32() {
    assert(42 == ss::parse_uint32("42"));
    assert(4294967295 == ss::parse_uint32("4294967295"));
    bool catched_overflow_negative = false;
    try {
        ss::parse_uint32("-42");
    } catch (const std::exception& e) {
        (void) e;
        catched_overflow_negative = true;
    }
    assert(catched_overflow_negative);
    bool catched_overflow_big = false;
    try {
        ss::parse_uint32("4294967296");
    } catch (const std::exception& e) {
        (void) e;
        catched_overflow_big = true;
    }
    assert(catched_overflow_big);
    bool catched_invalid = false;
    try {
        ss::parse_uint32("4242A");
    } catch (const std::exception& e) {
        (void) e;
        catched_invalid = true;
    }
    assert(catched_invalid);
}

void test_parse_int64() {
    assert(42 == ss::parse_int64("42"));
    assert(-42 == ss::parse_int64("-42"));
    bool catched_overflow_big = false;
    try {
        ss::parse_int64("9223372036854775808");
    } catch (const std::exception& e) {
        (void) e;
        catched_overflow_big = true;
    }
    assert(catched_overflow_big);
    bool catched_invalid = false;
    try {
        ss::parse_int64("-4242A");
    } catch (const std::exception& e) {
        (void) e;
        catched_invalid = true;
    }
    assert(catched_invalid);
}

void test_parse_uint64() {
    assert(42 == ss::parse_uint64("42"));
    assert(18446744073709551615u == ss::parse_uint64("18446744073709551615"));
//    bool catched_overflow_negative = false;
//    try {
//        auto parsed = ss::parse_uint64("-42");
//        std::cout << parsed << std::endl;
//    } catch (const std::exception& e) {
//        (void) e;
//        catched_overflow_negative = true;
//    }
//    assert(catched_overflow_negative);
    bool catched_overflow_big = false;
    try {
        ss::parse_uint64("18446744073709551616");
    } catch (const std::exception& e) {
        (void) e;
        catched_overflow_big = true;
    }
    assert(catched_overflow_big);
    bool catched_invalid = false;
    try {
        ss::parse_uint64("4242A");
    } catch (const std::exception& e) {
        (void) e;
        catched_invalid = true;
    }
    assert(catched_invalid);
}

} // namespace

int main() {
    test_parse_int16();
    test_parse_uint16();
    test_parse_int32();
    test_parse_uint32();
    test_parse_int64();
    test_parse_uint64();
    
    return 0;
}

