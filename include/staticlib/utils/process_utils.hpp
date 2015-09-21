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
 * File:   process_utils.hpp
 * Author: alex
 *
 * Created on September 21, 2015, 8:44 AM
 */

#ifndef STATICLIB_PROCESS_UTILS_HPP
#define	STATICLIB_PROCESS_UTILS_HPP

#include <string>

namespace staticlib {
namespace utils {

/**
 * Starts shell process with the specified command and waits for it to exit
 * 
 * @param cmd command to execute in shell
 * @return command return code
 */
int shell_exec_and_wait(const std::string& cmd);

} // namespace
}

#endif	/* STATICLIB_PROCESS_UTILS_HPP */

