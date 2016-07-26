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
 * File:   string_utils.cpp
 * Author: alex
 *
 * Created on January 13, 2015, 9:03 PM
 */

#include "staticlib/utils/string_utils.hpp"

#include <string>
#include <exception>
#include <sstream>
#include <cstdlib>
#include <cstring>


namespace staticlib {
namespace utils {

namespace { // anonymous

namespace sc = staticlib::config;

template <typename T>
T* get_buffer_internal(std::basic_string<T>& str, typename std::basic_string<T>::size_type required_size) {
    try {
        str.resize(required_size);
        return &str.front();
    } catch (const std::exception& e) {
        throw UtilsException(TRACEMSG(e.what() + 
                "\nError getting buffer with required size: [" + sc::to_string(required_size) + "]" + 
                " from string, length: [" + sc::to_string(str.length()) + "]"));
    }
}

} // namespace

char* get_buffer(std::string& str, std::string::size_type required_size) {
    return get_buffer_internal<char>(str, required_size);
}

wchar_t* get_buffer(std::wstring& str, std::wstring::size_type required_size) {
    return get_buffer_internal<wchar_t>(str, required_size);
}

char* alloc_copy(const std::string& str) STATICLIB_NOEXCEPT {
    auto len = str.length();
    char* msg = static_cast<char*> (malloc(len + 1));
    if (nullptr == msg) {
        char* err = static_cast<char*> (malloc(2));
        err[0] = 'E';
        err[1] = '\0';
        return err;
    }
    msg[len] = '\0';
    memcpy(msg, str.c_str(), len);
    return msg;
}

std::vector<std::string> split(const std::string& str, char delim) {
    std::stringstream ss{str};
    std::vector<std::string> res{};
    std::string item{};    
    while (std::getline(ss, item, delim)) {
        if (!item.empty()) {
            res.push_back(item);
        }
    }
    return res;
}

// http://stackoverflow.com/a/874160/314015
bool ends_with(std::string const& value, std::string const& ending) {
    if (value.length() >= ending.length()) {
        return (0 == value.compare(value.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}

std::string strip_filename(const std::string& file_path) {
    std::string::size_type pos = file_path.find_last_of("/\\");
    if (std::string::npos != pos && pos < file_path.length() - 1) {
        return std::string(file_path.data(), pos + 1);
    }
    return file_path;
}

} // namespace
} 

