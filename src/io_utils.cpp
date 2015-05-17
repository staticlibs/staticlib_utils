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
 * File:   io_utils.cpp
 * Author: alex
 * 
 * Created on April 6, 2015, 7:36 PM
 */

#include <istream>
#include <ostream>
#include <string>
#include <array>
#include <streambuf>

#include "staticlib/utils/string_utils.hpp"
#include "staticlib/utils/tracemsg.hpp"
#include "staticlib/utils/UtilsException.hpp"

#include "staticlib/utils/io_utils.hpp"

namespace staticlib {
namespace utils {

void write_all(std::streambuf& sink, const char* buf, std::streamsize buflen) {
    std::streamsize result = 0;
    while (result < buflen) {
        std::streamsize amt = sink.sputn(buf + result, buflen - result);
        result += amt;
    }
}

void write_all(std::streambuf& sink, const std::string& str) {
    write_all(sink, str.c_str(), static_cast<std::streamsize> (str.length()));
}

size_t read_all(std::streambuf& src, char* buf, std::streamsize buflen) {
    if (buflen < 0) return 0;
    size_t ulen = static_cast<size_t>(buflen);
    size_t result = 0;    
    while (result < ulen) {
        std::streamsize amt = src.sgetn(buf + result, buflen - result);
        if (0 == amt && std::char_traits<char>::eof() == src.sbumpc()) break;
        result += amt;        
    }
    return result;
}

void read_exact(std::streambuf& src, char* buf, std::streamsize buflen) {
    if (buflen < 0) return;
    size_t ulen = static_cast<size_t> (buflen);
    auto res = read_all(src, buf, buflen);
    if (res != ulen) throw UtilsException(TRACEMSG(
            std::string("Read amount: [" + to_string(res) + "]" +
            " of expected: [" + to_string(buflen) + "]")));
}

size_t copy_all(std::streambuf& src, std::streambuf& sink, char* buf, std::streamsize buflen) {
    if (buflen < 0) return 0;
    size_t ulen = static_cast<size_t> (buflen);
    size_t result = 0;
    size_t amt;
    while (ulen == (amt = read_all(src, buf, buflen))) {
        write_all(sink, buf, amt);
        result += amt;
    }
    // tail
    if (amt > 0) {
        write_all(sink, buf, amt);
        result += amt;
    }
    return result;
}


} // namespace
}
