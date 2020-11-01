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
 * File:   random_string_generator_test.cpp
 * Author: alex
 *
 * Created on July 3, 2015, 12:10 AM
 */

#include "staticlib/utils/random_string_generator.hpp"

#include <iostream>

#include "staticlib/config/assert.hpp"

void test_gen() {
    sl::utils::random_string_generator gen{};
    std::string str = gen.generate(42);
    slassert(42 == str.size());
    for (char ch : str) {
        int code = ch;
        int last = 'z';
        slassert(code <= last);
    }
}

void test_gen_fill() {
    sl::utils::random_string_generator gen{};
    std::string str{' ', 42};
    gen.generate(str);
    for (char ch : str) {
        slassert(' ' != ch);
    }
}

void test_charset() {
    sl::utils::random_string_generator gen{"a"};
    std::string str = gen.generate(42);
    slassert(42 == str.size());
    for (char ch : str) {
        slassert('a' == ch);
    }
}

void test_empty() {
    bool catched = false;
    try {
        sl::utils::random_string_generator gen{""};
        (void) gen;
    } catch (const sl::utils::utils_exception&) {
        catched = true;
    }
    slassert(catched);
}

int main() {
    try {
// Exception: Illegal on Ubuntu CI
#ifdef STATICLIB_WINDOWS
        test_gen();
        test_gen_fill();
        test_charset();
        test_empty();
#endif // STATICLIB_WINDOWS
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}
