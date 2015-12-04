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
 * File:   FileDescriptor_test.cpp
 * Author: alex
 *
 * Created on October 8, 2015, 5:17 PM
 */

#include "staticlib/utils/FileDescriptor.hpp"

#include <array>
#include <iostream>
#include <string>

#include "staticlib/config/assert.hpp"

namespace su = staticlib::utils;

void test_desc() {
    su::FileDescriptor desc{"CMakeCache.txt", 'r'};
}

void test_desc_fail() {
    bool catched = false;
    try {
        su::FileDescriptor desc{"aaa", 'r'}; 
    } catch (const su::UtilsException&) {
        catched = true;
    }
    slassert(catched);
}

void test_read() {
    su::FileDescriptor desc{"CMakeCache.txt", 'r'};
    desc.seek(16);
    std::array<char, 12> buf;
    desc.read(buf.data(), buf.size());
    std::string res{buf.data(), buf.size()};
    slassert(res == "akeCache fil");
}

void test_write() {
    su::FileDescriptor desc{"FileDescriptor_test_out.txt", 'w'};
    desc.write("aaa", 3);
}

void test_size() {
    su::FileDescriptor desc{"FileDescriptor_test_out.txt", 'r'};
    slassert(3 == desc.size());
}

void test_move() {
    su::FileDescriptor desc{"FileDescriptor_test_out.txt", 'r'};
    su::FileDescriptor moved{std::move(desc)};
    slassert(3 == moved.size());
}

void test_accessors() {
    su::FileDescriptor file{"FileDescriptor_test_accessors.txt", 'w'};
    (void) file;
    slassert("FileDescriptor_test_accessors.txt" == file.get_file_path());
    slassert('w' == file.get_mode());
}

int main() {
    try {
        test_desc();
        test_desc_fail();
        test_read();
        test_write();
        test_size();
        test_move();
        test_accessors();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}

