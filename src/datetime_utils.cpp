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
 * File:   datetime_utils.cpp
 * Author: alex
 *
 * Created on February 18, 2018, 1:37 PM
 */

#include "staticlib/utils/datetime_utils.hpp"

#include <chrono>

namespace staticlib {
namespace utils {

// http://stackoverflow.com/a/2834294/314015
uint64_t current_time_millis() {
    auto time = std::chrono::system_clock::now();
    auto since_epoch = time.time_since_epoch();
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(since_epoch);
    return static_cast<uint64_t>(millis.count());
}

uint64_t current_time_millis_steady() {
    auto time = std::chrono::steady_clock::now();
    auto since_epoch = time.time_since_epoch();
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(since_epoch);
    return static_cast<uint64_t>(millis.count());
}

} // namespace
}
