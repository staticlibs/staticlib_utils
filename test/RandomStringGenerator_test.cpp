/* 
 * File:   RandomStringGenerator_test.cpp
 * Author: alex
 *
 * Created on July 3, 2015, 12:10 AM
 */

#include <iostream>

#include "staticlib/utils/assert.hpp"

#include "staticlib/utils/UtilsException.hpp"
#include "staticlib/utils/RandomStringGenerator.hpp"

namespace su = staticlib::utils;

void test_gen() {
    su::RandomStringGenerator gen{};
    std::string str = gen.generate(42);
    slassert(42 == str.size());
    for (char ch : str) {
        int code = ch;
        int last = 'z';
        slassert(code <= last);
    }
}

void test_gen_fill() {
    su::RandomStringGenerator gen{};
    std::string str{' ', 42};
    gen.generate(str);
    for (char ch : str) {
        slassert(' ' != ch);
    }
}

void test_charset() {
    su::RandomStringGenerator gen{"a"};
    std::string str = gen.generate(42);
    slassert(42 == str.size());
    for (char ch : str) {
        slassert('a' == ch);
    }
}

void test_empty() {
    bool catched = false;
    try {
        su::RandomStringGenerator gen{""};
        (void) gen;
    } catch (const su::UtilsException&) {
        catched = true;
    }
    slassert(catched);
}

int main() {
    try {
        test_gen();
        test_gen_fill();
        test_charset();
        test_empty();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}
