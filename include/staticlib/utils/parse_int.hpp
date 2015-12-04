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
 * File:   parse_int.hpp
 * Author: alex
 *
 * Created on January 31, 2015, 3:41 PM
 */

#ifndef STATICLIB_UTILS_PARSE_INT_HPP
#define	STATICLIB_UTILS_PARSE_INT_HPP

#include <string>
#include <cstdint>

#include "staticlib/utils/UtilsException.hpp"

// std::stoi is not available on Android in NDK 9

namespace staticlib {
namespace utils {

/**
 * Parses `int16_t` with base 10 from specified string using `strto*l`
 * 
 * @param str string containing exactly one `int16_t` value
 * @return `int16_t` value
 */
int16_t parse_int16(const std::string& str);

/**
 * Parses `uint16_t` with base 10 from specified string using `strto*l`
 * 
 * @param str string containing exactly one `uint16_t` value
 * @return `uint16_t` value
 */
uint16_t parse_uint16(const std::string& str);

/**
 * Parses `int32_t` with base 10 from specified string using `strto*l`
 * 
 * @param str string containing exactly one `uint32_t` value
 * @return `int32_t` value
 */
int32_t parse_int32(const std::string& str);

/**
 * Parses `uint32_t` with base 10 from specified string using `strto*l`
 * 
 * @param str string containing exactly one `uint32_t` value
 * @return `uint32_t` value
 */
uint32_t parse_uint32(const std::string& str);

/**
 * Parses `int64_t` with base 10 from specified string using `strto*l`
 * 
 * @param str string containing exactly one `uint64_t` value
 * @return `int64_t` value
 */
int64_t parse_int64(const std::string& str);

/**
 * Parses `uint64_t` with base 10 from specified string using `strto*l`
 * 
 * @param str string containing exactly one `uint64_t` value
 * @return `uint64_t` value
 */
uint64_t parse_uint64(const std::string& str);

} // namespace
}

#endif	/* STATICLIB_UTILS_PARSE_INT_HPP */

