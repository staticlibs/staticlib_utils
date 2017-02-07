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
 * File:   random_string_generator.cpp
 * Author: alex
 * 
 * Created on July 3, 2015, 12:09 AM
 */

#include "staticlib/utils/random_string_generator.hpp"

#include <string>
#include <random>
#include <utility>
#include <cstdint>

namespace staticlib {
namespace utils {

// see: http://stackoverflow.com/a/9789249/314015
random_string_generator::random_string_generator(random_string_generator&& other) :
charset(std::move(other.charset)),
engine(std::move(other.engine)),
dist(std::move(other.dist)) { }


random_string_generator& random_string_generator::operator=(random_string_generator&& other) {
    this->charset = std::move(other.charset);
    this->engine = std::move(other.engine);
    this->dist = std::move(other.dist);
    return *this;
}

random_string_generator::random_string_generator() :
random_string_generator("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789") { }

random_string_generator::random_string_generator(std::string charset) :
charset(std::move(charset)),
engine(std::random_device{}()),
dist(static_cast<size_t>(0), this->charset.size() - 1) {
    if(this->charset.empty()) throw utils_exception(TRACEMSG("Invalid empty charset specified"));
}


std::string random_string_generator::generate(uint32_t length) {
    std::string res(length, '#');
    generate(res);
    return res;
}

void random_string_generator::generate(std::string& str) {
    for (char& ch : str) {
        ch = charset[dist(engine)];
    } 
}

}
} // namespace
