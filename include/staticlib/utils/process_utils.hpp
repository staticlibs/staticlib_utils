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

#ifndef STATICLIB_UTILS_PROCESS_UTILS_HPP
#define	STATICLIB_UTILS_PROCESS_UTILS_HPP

#include <vector>

#ifdef STATICLIB_WITH_ICU
#include <unicode/unistr.h>
#else
#include <string>
#endif // STATICLIB_WITH_ICU

#include "staticlib/utils/UtilsException.hpp"

namespace staticlib {
namespace utils {

/**
 * Starts shell process with the specified command and waits for it to exit
 * 
 * @param cmd command to execute in shell
 * @return command return code
 */
#ifdef STATICLIB_WITH_ICU
int shell_exec_and_wait(const icu::UnicodeString& cmd);
#else
int shell_exec_and_wait(const std::string& cmd);
#endif // STATICLIB_WITH_ICU

/**
 * Starts the process with the specified command and waits for it to exit
 * 
 * @param executable path to executable binary or script
 * @param args list of arguments
 * @return command return code
 */
#ifdef STATICLIB_WITH_ICU
int exec_and_wait(const icu::UnicodeString& executable, const std::vector<icu::UnicodeString>& args, const icu::UnicodeString& out);
#else
int exec_and_wait(const std::string& executable, const std::vector<std::string>& args, const std::string& out);
#endif // STATICLIB_WITH_ICU

/**
 * Starts the process with the specified command and waits for it to exit
 * 
 * @param executable path to executable binary or script
 * @param args list of arguments
 * @return child process pid
 */
#ifdef STATICLIB_WITH_ICU
int exec_async(const icu::UnicodeString& executable, const std::vector<icu::UnicodeString>& args, const icu::UnicodeString& out);
#else
int exec_async(const std::string& executable, const std::vector<std::string>& args, const std::string& out);
#endif // STATICLIB_WITH_ICU

/**
 * Returns path to the current executable file
 * 
 * @return path to the current executable file
 */
#ifdef STATICLIB_WITH_ICU
icu::UnicodeString current_executable_path();
#else
std::string current_executable_path();
#endif // STATICLIB_WITH_ICU

} // namespace
}

#endif	/* STATICLIB_UTILS_PROCESS_UTILS_HPP */

