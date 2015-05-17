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
 * File:   BaseException.cpp
 * Author: alex
 * 
 * Created on January 2, 2015, 12:03 PM
 */

#include "staticlib/utils/config.hpp"
#include "staticlib/utils/BaseException.hpp"

namespace staticlib {
namespace utils {

BaseException::BaseException(std::string msg) : message(msg) { }

const char* BaseException::what() const STATICLIB_NOEXCEPT {
    return message.c_str();
}

}
} //namespace
