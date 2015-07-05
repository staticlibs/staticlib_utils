/* 
 * File:   RandomStringGenerator_test.cpp
 * Author: alex
 *
 * Created on July 3, 2015, 12:10 AM
 */

#include <iostream>
#include <cassert>

#include "staticlib/utils/UtilsException.hpp"
#include "staticlib/utils/RandomStringGenerator.hpp"

namespace { // anonymous

namespace su = staticlib::utils;

void test_gen() {
    su::RandomStringGenerator gen{};
    std::string str = gen.generate(42);
    assert(42 == str.size());
    for (char ch : str) {
        int code = ch;
        int last = 'z';
        (void) code; (void) last; assert(code <= last);
    }
}

void test_gen_fill() {
    su::RandomStringGenerator gen{};
    std::string str{' ', 42};
    gen.generate(str);
    for (char ch : str) {
        (void) ch; assert(' ' != ch);
    }
}

void test_charset() {
    su::RandomStringGenerator gen{"a"};
    std::string str = gen.generate(42);
    assert(42 == str.size());
    for (char ch : str) {
        (void) ch; assert('a' == ch);
    }
}

void test_empty() {
    bool catched = false;
    try {
        su::RandomStringGenerator gen{""};
        (void) gen;
    } catch (su::UtilsException e) {
        (void) e;
        catched = true;
    }
    (void) catched; assert(catched);
}

} // namespace

int main() {
    test_gen();
    test_gen_fill();
    test_charset();
    test_empty();
    return 0;
}

