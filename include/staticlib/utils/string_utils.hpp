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
 * File:   string_utils.hpp
 * Author: alex
 *
 * Created on January 2, 2015, 12:59 PM
 */

#ifndef STATICLIB_UTILS_STRING_UTILS_HPP
#define	STATICLIB_UTILS_STRING_UTILS_HPP

#include <string>
#include <sstream>
#include <typeinfo>
#include <vector>
#include <cstdint>

#include "staticlib/config.hpp"
#include "staticlib/utils/UtilsException.hpp"

namespace staticlib {
namespace utils {

/**
 * Access underlying string buffer as writable char array safely (according to C++11)
 * Will resize specified string (memory will be default-initialized).
 * 
 * @param str string instance
 * @param required_size required size of the buffer, string will be resized to this size
 * @return writable buffer owned by the specified string
 */
char* get_buffer(std::string& str, std::string::size_type required_size);

/**
 * Access underlying wide string buffer as writable char array safely (according to C++11)
 * Will resize specified string (memory will be default-initialized).
 * 
 * @param str wide string instance
 * @param required_size required size of the buffer, string will be resized to this size
 * @return writable buffer owned by the specified string
 */
wchar_t* get_buffer(std::wstring& str, std::wstring::size_type required_size);

/**
 * Allocates a buffer and copies there contents of the string.
 * Allocated buffer must be freed by the caller.
 * 
 * @param str string to copy
 * @return allocated buffer
 */
char* alloc_copy(const std::string& str) STATICLIB_NOEXCEPT;

/**
 * Splits string into vector using specified character as a delimiter,
 * empty result parts are ignored
 * 
 * @param str string to split
 * @param delim delimiter character
 * @return vector containing splitted parts
 */
std::vector<std::string> split(const std::string& str, char delim);

} // namespace
}

#endif	/* STATICLIB_UTILS_STRING_UTILS_HPP */

