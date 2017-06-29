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

#include "staticlib/utils/string_utils.hpp"

#include <cstring>
#include <iostream>

#include "staticlib/config/assert.hpp"

void test_alloc_copy() {
    std::string st{"foo"};
    auto buf = sl::utils::alloc_copy(st);
    slassert(3 == strlen(buf));
    slassert('\0' == buf[3]);
    free(buf);
}

void test_split() {
    std::string src{"foo:bar::baz:"};
    std::vector<std::string> vec = sl::utils::split(src, ':');
    slassert(3 == vec.size());
    slassert("foo" == vec[0]);
    slassert("bar" == vec[1]);
    slassert("baz" == vec[2]);
}

void test_starts_with() {
    slassert(sl::utils::starts_with("foo", "fo"));
    slassert(sl::utils::starts_with("foo", "foo"));
    slassert(!sl::utils::starts_with("foo", "1foo"));
    slassert(sl::utils::starts_with("foo", ""));
    slassert(!sl::utils::starts_with("foo", "ba"));
}

void test_ends_with() {
    slassert(sl::utils::ends_with("foo", "oo"));
    slassert(sl::utils::ends_with("foo", "foo"));
    slassert(!sl::utils::ends_with("foo", "1foo"));
    slassert(sl::utils::ends_with("foo", ""));
    slassert(!sl::utils::ends_with("foo", "ar"));
}

void test_strip_filename() {
    slassert("/foo/bar/" == sl::utils::strip_filename("/foo/bar/baz"));
    slassert("c:\\foo\\bar\\" == sl::utils::strip_filename("c:\\foo\\bar\\baz"));
    slassert("/foo/bar/" == sl::utils::strip_filename("/foo/bar/baz.foo"));
    slassert("/foo/bar/" == sl::utils::strip_filename("/foo/bar/"));
    slassert("/" == sl::utils::strip_filename("/foo"));
    slassert("foo" == sl::utils::strip_filename("foo"));
    slassert("" == sl::utils::strip_filename(""));
}

void test_strip_parent_dir() {    
    slassert("baz" == sl::utils::strip_parent_dir("/foo/bar/baz"));
    slassert("baz" == sl::utils::strip_parent_dir("c:\\foo\\bar\\baz"));
    slassert("baz.foo" == sl::utils::strip_parent_dir("/foo/bar/baz.foo"));
    slassert("bar/" == sl::utils::strip_parent_dir("/foo/bar/"));
    slassert("bar/" == sl::utils::strip_parent_dir("/foo///bar/"));
    slassert("bar//" == sl::utils::strip_parent_dir("/foo/bar//"));
    slassert("foo" == sl::utils::strip_parent_dir("/foo"));
    slassert("foo" == sl::utils::strip_parent_dir("c:\\bar\\foo"));    
    slassert("foo" == sl::utils::strip_parent_dir("foo"));    
    slassert("a" == sl::utils::strip_parent_dir("/a"));
    slassert("/" == sl::utils::strip_parent_dir("/"));
    slassert("///" == sl::utils::strip_parent_dir("///"));
    slassert("\\" == sl::utils::strip_parent_dir("\\"));
    slassert("" == sl::utils::strip_parent_dir(""));
}

void test_trim() {
    slassert("foo" == sl::utils::trim(" foo  "));
    slassert("foo" == sl::utils::trim("  foo"));
    slassert("foo" == sl::utils::trim("foo "));
    slassert("foo  bar" == sl::utils::trim(" foo  bar  "));
    slassert("" == sl::utils::trim(""));
}

void test_iequals() {
    slassert(sl::utils::iequals("foo", "FoO"));
    slassert(sl::utils::iequals("foo", "foo"));
    slassert(!sl::utils::iequals("foo", "boo"));
}

void test_repace() {
    std::string str1 = "foobarfoobaz";
    slassert("42bar42baz" == sl::utils::replace_all(str1, "foo", "42"));
    std::string str2 = "foo";
    slassert("foo" == sl::utils::replace_all(str2, "bar", ""));
    std::string str3 = "foo";
    slassert("foo" == sl::utils::replace_all(str3, "", "42"));
}

int main() {
    try {
        test_alloc_copy();
        test_split();
        test_starts_with();
        test_ends_with();
        test_strip_filename();
        test_strip_parent_dir();
        test_trim();
        test_iequals();
        test_repace();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}

