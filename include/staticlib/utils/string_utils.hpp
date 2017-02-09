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
#include "staticlib/utils/utils_exception.hpp"

namespace staticlib {
namespace utils {

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

/**
 * Checks whether one string ends with another one
 * 
 * @param value string to check
 * @param ending string ending
 * @return true if string ends with specified ending, false otherwise
 */
bool ends_with(const std::string& value, const std::string& ending);

/**
 * Returns new string containing specified path but without
 * the filename (last non-ending-with-slash element of the path)
 * 
 * @param file_path file path
 * @return parent directory path
 */
std::string strip_filename(const std::string& file_path);

/**
 * Returns new string containing specified path but without
 * the parent directory (without everything before the 
 * last non-ending-with-slash element of the path)
 * 
 * @param file_path file path
 * @return filename
 */
std::string strip_parent_dir(const std::string& file_path);

/**
 * Reference to empty string
 * 
 * @return empty string reference
 */
const std::string& empty_string();

} // namespace
}

#endif	/* STATICLIB_UTILS_STRING_UTILS_HPP */

