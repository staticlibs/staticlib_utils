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
 * File:   memory_utils_test.cpp
 * Author: alex
 *
 * Created on January 2, 2015, 1:07 PM
 */

#include <cassert>
#include <string>

#include "staticlib/utils/memory_utils.hpp"

namespace { // anonymous

namespace ss = staticlib::utils;

void test_make_unique() {
    auto ptr = ss::make_unique<std::string>("42");
    assert("42" == *ptr.get());
}

void test_free_deleter() {
    char* ptr = static_cast<char*> (malloc(42));
    std::unique_ptr<char, ss::free_deleter<char>> uptr{ptr, ss::free_deleter<char>()};
    (void) uptr;
    // memory will be freed on scope exit
}

} // namespace



int main() {
    test_make_unique();
    test_free_deleter();

    
    return 0;
}

