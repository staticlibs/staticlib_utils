/*
 * Copyright 2017, alex at staticlibs.net
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
 * File:   url_utils.hpp
 * Author: alex
 *
 * Created on May 11, 2017, 10:53 PM
 */

#ifndef STATICLIB_UTILS_URL_UTILS_HPP
#define	STATICLIB_UTILS_URL_UTILS_HPP

#include <string>

namespace staticlib {
namespace utils {

/**
 * Unescapes specified URL-encoded string (a%20value+with%20spaces)
 * 
 * @param str URL-encoded string
 * @return unescaped (plain) string
 */
std::string url_decode(const std::string& str);

/**
 * Encodes specified string so that it is safe for URLs (with%20spaces)
 * 
 * @param str string to encode
 * @return escaped string
 */
std::string url_encode(const std::string& str);

} // namespace
}

#endif	/* STATICLIB_UTILS_URL_UTILS_HPP */

