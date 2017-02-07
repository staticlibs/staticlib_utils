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
 * File:   windows.hpp
 * Author: alex
 *
 * Created on March 16, 2015, 9:53 PM
 */

#ifndef STATICLIB_UTILS_WINDOWS_HPP
#define	STATICLIB_UTILS_WINDOWS_HPP

#include <string>
#include <cstdint>

#include "staticlib/config.hpp"

#include "staticlib/utils/utils_exception.hpp"

namespace staticlib {
namespace utils {

/**
 * Convert string from UTF-8 multibyte to UTF-16 widechar
 * 
 * @param st UTF-8 multibyte string
 * @return UTF-16 wide string
 */
std::wstring widen(const std::string& st);

/**
 * Convert string from UTF-16 widechar to UTF-8 multibyte
 * 
 * @param wstring UTF-16 wide string
 * @return UTF-8 multibyte string
 */
std::string narrow(std::wstring wstr);

/**
 * Convert buffer from UTF-16 widechar to UTF-8 multibyte
 * 
 * @param wbuf UTF-16 widechar buffer
 * @param length buffer length in wide chars
 * @return UTF-8 multibyte string
 */
std::string narrow(const wchar_t* wbuf, size_t length);

/**
 * Convert Windows system error code (http://msdn.microsoft.com/en-us/library/windows/desktop/ms681381%28v=vs.85%29.aspx)
 * to english message
 * 
 * @param code error code
 * @return message in english
 */
std::string errcode_to_string(uint32_t code) STATICLIB_NOEXCEPT;

} //namespace
}

#endif	/* STATICLIB_UTILS_WINDOWS_HPP */

