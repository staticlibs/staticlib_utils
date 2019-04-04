/*
 * Copyright 2019, alex at staticlibs.net
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
 * File:   user_utils.hpp
 * Author: alex
 *
 * Created on April 4, 2019, 2:36 PM
 */

#ifndef STATICLIB_UTILS_USER_UTILS_HPP
#define STATICLIB_UTILS_USER_UTILS_HPP

#include <string>

namespace staticlib {
namespace utils {

/**
 * Returns name of the user that runs current process
 * 
 * @return name of the user that runs current process
 */
std::string user_name();

/**
 * Returns home directory of the user that runs current process
 * 
 * @return home directory of the user that runs current process
 */
std::string user_home_dir();

/**
 * Returns local app data directory of the user that runs current process
 * 
 * @return local app data directory of the user that runs current process
 */
std::string user_localappdata_dir();

} // namespace
}

#endif /* STATICLIB_UTILS_USER_UTILS_HPP */

