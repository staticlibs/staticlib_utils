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
 * File:   tracemsg.hpp
 * Author: alex
 *
 * Created on January 2, 2015, 11:53 AM
 */

#ifndef STATICLIB_TRACEMSG_HPP
#define	STATICLIB_TRACEMSG_HPP

#include <string>

#include "staticlib/utils/config.hpp"

#define TRACEMSG(message) staticlib::utils::tracemsg(message, __FILE__, STATICLIB_CURRENT_FUNCTION, __LINE__)

namespace staticlib {
namespace utils {

/**
 * Prepends specified message with formatted current function name, source file name and line number.
 * Can be used through macro shortcut as `TRACEMSG("Hi")`
 * 
 * @param message input message
 * @param file source filename, `__FILE__` macro is used in `TRACEMSG` macro
 * @param func current function name, `STATICLIB_CURRENT_FUNCTION` macro is used in `TRACEMSG` macro
 * @param line current line in source file, `__LINE__` macro is used in `TRACEMSG` macro
 * @return message string prepended with specified data
 */
std::string tracemsg(const std::string& message, const std::string& file, const std::string& func, int line);

} //namespace
}


#endif	/* STATICLIB_TRACEMSG_HPP */

