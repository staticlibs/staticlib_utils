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
 * File:   parse_int.cpp
 * Author: alex
 * 
 * Created on January 31, 2015, 3:51 PM
 */

#include <cstdlib>
#include <cerrno>
#include <climits>

#include "staticlib/utils/UtilsException.hpp"
#include "staticlib/utils/tracemsg.hpp"
#include "staticlib/utils/parse_int.hpp"

namespace staticlib {
namespace utils {

int16_t parse_int16(const std::string& str) {
    auto cstr = str.c_str();
    char* endptr;
    errno = 0;
    auto l = strtol(cstr, &endptr, 0);
    if (errno == ERANGE || cstr + str.length() != endptr) {
        throw UtilsException(TRACEMSG(std::string("Cannot parse int16_t from string:[" + str + "]")));
    }
    if (l < SHRT_MIN || l > SHRT_MAX) {
        throw UtilsException(TRACEMSG(std::string("Value overflow for int16_t from string:[" + str + "]")));
    }
    return static_cast<int16_t> (l);
}

uint16_t parse_uint16(const std::string& str) {
    auto cstr = str.c_str();
    char* endptr;
    errno = 0;
    auto l = strtol(cstr, &endptr, 0);
    if (errno == ERANGE || cstr + str.length() != endptr) {
        throw UtilsException(TRACEMSG(std::string("Cannot parse uint16_t from string:[" + str + "]")));
    }
    if (l < 0 || l > USHRT_MAX) {
        throw UtilsException(TRACEMSG(std::string("Value overflow for uint16_t from string:[" + str + "]")));
    }
    return static_cast<uint16_t> (l);
}

int32_t parse_int32(const std::string& str) {
    auto cstr = str.c_str();
    char* endptr;
    errno = 0;
    auto l = strtol(cstr, &endptr, 0);
    if (errno == ERANGE || cstr + str.length() != endptr) {
        throw UtilsException(TRACEMSG(std::string("Cannot parse int32_t from string:[" + str + "]")));
    }
    if (l < INT_MIN || l > INT_MAX) {
        throw UtilsException(TRACEMSG(std::string("Value overflow for int32_t from string:[" + str + "]")));
    }
    return static_cast<int32_t> (l);
}

uint32_t parse_uint32(const std::string& str) {
    auto cstr = str.c_str();
    char* endptr;
    errno = 0;
    auto l = strtoll(cstr, &endptr, 0);
    if (errno == ERANGE || cstr + str.length() != endptr) {
        throw UtilsException(TRACEMSG(std::string("Cannot parse uint32_t from string:[" + str + "]")));
    }
    if (l < 0 || l > UINT_MAX) {
        throw UtilsException(TRACEMSG(std::string("Value overflow for uint32_t from string:[" + str + "]")));
    }
    return static_cast<uint32_t> (l);
}

int64_t parse_int64(const std::string& str) {
    auto cstr = str.c_str();
    char* endptr;
    errno = 0;
    auto l = strtoll(cstr, &endptr, 0);
    if (errno == ERANGE || cstr + str.length() != endptr) {
        throw UtilsException(TRACEMSG(std::string("Cannot parse int64_t from string:[" + str + "]")));
    }
    return static_cast<int64_t> (l);
}

uint64_t parse_uint64(const std::string& str) {
    auto cstr = str.c_str();
    char* endptr;
    errno = 0;
    auto l = strtoull(cstr, &endptr, 0);
    if (errno == ERANGE || cstr + str.length() != endptr) {
        throw UtilsException(TRACEMSG(std::string("Cannot parse uint64_t from string:[" + str + "]")));
    }
    return static_cast<uint64_t> (l);
}

} // namespace
}
