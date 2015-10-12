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
 * File:   file_io_test.cpp
 * Author: alex
 *
 * Created on October 8, 2015, 5:17 PM
 */

#include <iostream>
#include <string>
#include <array>
#include <cassert>

#include "staticlib/utils/file_io.hpp"
#include "staticlib/utils/UtilsException.hpp"

namespace { // anonymous

namespace su = staticlib::utils;

void test_desc() {
    //try {
    su::FileDescriptor desc{"CMakeCache.txt", 'r'};
    //} catch (const std::exception& e) {
    //    std::cout << e.what() << std::endl;
    //}
}

void test_desc_fail() {
    bool catched = false;
    try {
        su::FileDescriptor desc{"aaa", 'r'}; 
    } catch (const su::UtilsException& e) {
        (void) e;
        catched = true;
    }
    (void) catched;
    assert(catched);
}

void test_read() {
    su::FileDescriptor desc{"CMakeCache.txt", 'r'};
    desc.seek(16);
    std::array<char, 12> buf;
    desc.read(buf.data(), buf.size());
    std::string res{buf.data(), buf.size()};
    (void) res;
    assert(res == "akeCache fil");
}

void test_write() {
    su::FileDescriptor desc{"file_io_test_out.txt", 'w'};
    desc.write("aaa", 3);
}

void test_size() {
    su::FileDescriptor desc{"file_io_test_out.txt", 'r'};
    assert(3 == desc.size());
}

}

int main() {
    test_desc();
    test_desc_fail();
    test_read();
    test_write();
    test_size();
    
    return 0;
}

