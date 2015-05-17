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
 * File:   io_utils_test.cpp
 * Author: alex
 *
 * Created on April 6, 2015, 7:20 PM
 */

#include <string>
#include <array>
#include <iostream>
#include <sstream>
#include <cassert>
#include <fstream>

#include "staticlib/utils/UtilsException.hpp"
#include "staticlib/utils/io_utils.hpp"

namespace { // anonymous

namespace si = staticlib::utils;

class TwoBytesAtOnceSink {
    std::string& dest;

public:
    typedef char char_type;
//    typedef boost::iostreams::sink_tag category;

    TwoBytesAtOnceSink& operator=(const TwoBytesAtOnceSink&) = delete;

    TwoBytesAtOnceSink(std::string& dest) : dest(dest) { }

    std::streamsize write(const char* s, std::streamsize n) {
        std::streamsize len = n >= 2 ? 2 : n;
        for (std::streamsize i = 0; i < len; i++) {
            dest.push_back(s[i]);
        }
        return len;
    }
};

class TwoBytesAtOnceSource {
    const std::string& src;
    size_t ind = 0;

public:
    typedef char char_type;
//    typedef boost::iostreams::source_tag category;

    TwoBytesAtOnceSource& operator=(const TwoBytesAtOnceSource&) = delete;

    TwoBytesAtOnceSource(const std::string& src) : src(src) { }

    std::streamsize read(char* s, std::streamsize n) {
        std::streamsize len = n >= 2 ? 2 : n;
        for (std::streamsize i = 0; i < len; i++) {
            s[i] = src[ind++];
        }
        return len;
    }
};

void test_write_not_all() {
    std::string res{};
    TwoBytesAtOnceSink out{res};
    si::unbuffered_sink<TwoBytesAtOnceSink> streambuf{out};
    auto written = streambuf.sputn("abc", 3);
    (void) written;
    assert(2 == written);
    assert(2 == res.length());
    assert("ab" == res);
}

void test_write_all_buffer() {
    std::string res{};
    TwoBytesAtOnceSink out{res};
    si::unbuffered_sink<TwoBytesAtOnceSink> streambuf{out};
    si::write_all(streambuf, "abc", 3);
    assert(3 == res.length());
    assert("abc" == res);
}

void test_write_all_str() {
    std::string res{};
    TwoBytesAtOnceSink out{res};
    si::unbuffered_sink<TwoBytesAtOnceSink> streambuf{out};
    std::string data{"abc"};
    si::write_all(streambuf, data);    
    assert(3 == res.length());
    assert("abc" == res);
}

void test_read_not_all() {
    std::string src{"abc"};
    TwoBytesAtOnceSource in{src};
    si::unbuffered_source<TwoBytesAtOnceSource> streambuf{in};
    std::array<char, 4> buf{{}};
    auto read = streambuf.sgetn(buf.data(), 3);
    (void) read;
    assert(2 == read);
    std::string res{buf.data()};
    assert(2 == res.length());
    assert("ab" == res);
}

void test_read_all() {
    std::string src{"abc"};
    TwoBytesAtOnceSource in{src};
    si::unbuffered_source<TwoBytesAtOnceSource> streambuf{in};
    std::array<char, 4> buf{{}};
    auto read = si::read_all(streambuf, buf.data(), 3);
    (void) read;
    assert(3 == read);
    std::string res{buf.data()};
    assert(3 == res.length());
    assert("abc" == res);
}

void test_read_exact() {
    std::string src{"abc"};
    std::istringstream in{src};
    std::array<char, 5> buf{{}};
    bool thrown = false;
    try {
        si::read_exact(*in.rdbuf(), buf.data(), 4);
    } catch (const si::UtilsException& e) {
        (void) e;
        thrown = true;
    }
    (void) thrown;
    assert(thrown);
}

void test_copy() {
    std::string res{};
    TwoBytesAtOnceSink out{res};
    si::unbuffered_sink<TwoBytesAtOnceSink> streambuf{out};
    std::array<char, 2> buf{{}};
    std::string src = "abc";
    std::istringstream in{src};
    auto copied = si::copy_all(*in.rdbuf(), streambuf, buf.data(), buf.size());
    (void) copied;
    assert(3 == copied);
    assert(3 == res.length());
    assert("abc" == res);
}

void test_unbuffered_source_fail() {
    std::string src{"abc"};
    TwoBytesAtOnceSource in{src};
    si::unbuffered_source<TwoBytesAtOnceSource> streambuf{in};
    std::istream stream{&streambuf};
    std::string res{};
    bool catched = false;
    try {
        stream >> res;
    } catch (const si::UtilsException& e) {
        (void) e;
        catched = true;
    }
    (void) catched;
    assert(catched);
}

void test_unbuffered_sink_fail() {
    std::string res{};
    TwoBytesAtOnceSink out{res};
    si::unbuffered_sink<TwoBytesAtOnceSink> streambuf{out};
    std::string src = "abc";
    std::ostream stream{&streambuf};
    stream << src;
    assert("ab" == res);
}

} // namespace

int main() {
    test_write_not_all();
    test_write_all_buffer();
    test_write_all_str();
    test_read_not_all();
    test_read_all();
    test_read_exact();
    test_copy();
    test_unbuffered_source_fail();
    test_unbuffered_sink_fail();

    return 0;
}
