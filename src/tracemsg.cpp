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
 * File:   tracemsg.cpp
 * Author: alex
 * 
 * Created on January 2, 2015, 12:04 PM
 */

#include <string>

#include "staticlib/utils/string_utils.hpp"
#include "staticlib/utils/tracemsg.hpp"

namespace staticlib {
namespace utils {

namespace {

std::string extract_filename(const std::string& str) {        
    auto slash_ind = str.find_last_of("/");
    if (std::string::npos != slash_ind && str.length() > slash_ind) {
        return str.substr(slash_ind + 1);
    } else {
        auto backslash_ind = str.find_last_of("\\");
        if (std::string::npos != backslash_ind && str.length() > backslash_ind) {
            return str.substr(backslash_ind + 1);
        }
    }
    return str;
}

std::string extract_function_name(const std::string& str) {    
    auto paren_ind = str.find("(");
    auto funcsig = std::string::npos != paren_ind ? str.substr(0, paren_ind) : str;
    auto space_ind = funcsig.find_last_of(" ");
    if (std::string::npos != space_ind && funcsig.length() > space_ind) {
        return funcsig.substr(space_ind + 1);
    }
    return funcsig;
}

} // namespace

std::string tracemsg(const std::string& message, const std::string& file, const std::string& func, int line) {
    return std::string()
            .append(message)
            .append("\n    at ")
            .append(extract_function_name(func))
            .append("(")
            .append(extract_filename(file))
            .append(":")
            .append(to_string(line))
            .append(")");
}

}
} //namespace
