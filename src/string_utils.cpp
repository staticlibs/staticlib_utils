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

#include <cctype>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <string>
#include <exception>
#include <sstream>

namespace staticlib {
namespace utils {

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

// http://stackoverflow.com/a/8095276/314015
bool starts_with(const std::string& value, const std::string& start) {
    return 0 == value.compare(0, start.length(), start);
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
    return std::string(file_path.data(), file_path.length());
}

std::string strip_parent_dir(const std::string& file_path) {
    std::string::size_type pos = file_path.find_last_of("/\\");
    if (std::string::npos == pos) {
        return std::string(file_path.data(), file_path.length());
    } 
    if (file_path.length() == pos) {
        return std::string();
    }
    return std::string(file_path, pos + 1);
}

// http://stackoverflow.com/a/17976541
std::string trim(const std::string& s) {
    auto wsfront = std::find_if_not(s.begin(), s.end(), [](int c) {
        return std::isspace(c);
    });
    return std::string(wsfront, std::find_if_not(s.rbegin(), std::string::const_reverse_iterator(wsfront), [](int c) {
        return std::isspace(c);
    }).base());
}

// http://stackoverflow.com/a/27813
bool iequals(const std::string& str1, const std::string& str2) {
    if (str1.size() != str2.size()) {
        return false;
    }
    for (std::string::const_iterator c1 = str1.begin(), c2 = str2.begin(); c1 != str1.end(); ++c1, ++c2) {
        if (std::tolower(*c1) != std::tolower(*c2)) {
            return false;
        }
    }
    return true;
}

std::string& replace_all(std::string& str, const std::string& snippet, const std::string& replacement) {
    if (snippet.empty()) {
        return str;
    }
    auto pos = std::string::npos;
    while (std::string::npos != (pos = str.find(snippet))) {
        str.replace(pos, snippet.length(), replacement);
    }
    return str;
}

const std::string& empty_string() {
    static std::string empty{""};
    return empty;
}

} // namespace
} 

