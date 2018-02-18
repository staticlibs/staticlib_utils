/*
 * Copyright 2018, alex at staticlibs.net
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
 * File:   datetime_utils.hpp
 * Author: alex
 *
 * Created on February 18, 2018, 1:31 PM
 */

#ifndef STATICLIB_UTILS_DATETIME_UTILS_HPP
#define STATICLIB_UTILS_DATETIME_UTILS_HPP

#include <cstdint>

namespace staticlib {
namespace utils {

/**
 * Returns the current time in milliseconds obtained from 'system_clock'
 * 
 * @return current time in milliseconds
 */
uint64_t current_time_millis();

/**
 * Returns the current time in milliseconds obtained from 'steady_clock'
 * 
 * @return current time in milliseconds
 */
uint64_t current_time_millis_steady();

} // namespace
}

#endif /* STATICLIB_UTILS_DATETIME_UTILS_HPP */

