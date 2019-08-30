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
 * File:   process_utils_test.cpp
 * Author: alex
 *
 * Created on September 21, 2015, 8:53 AM
 */

#include "staticlib/utils/process_utils.hpp"

#include <cstring>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include "staticlib/config/assert.hpp"

#include "staticlib/config.hpp"

void test_shell_exec() {
    sl::utils::shell_exec_and_wait("echo aaa > echo_out.txt");
}

void test_exec_async() {
#ifdef STATICLIB_WINDOWS
    sl::utils::exec_async("c:/windows/system32/ipconfig", {"/all"}, "ipconfig_async_out.txt");
#else
    sl::utils::exec_async("/bin/ls", {"-l", "-a", "-h"}, "ls_async_out.txt");
#endif // STATICLIB_WINDOWS
}

void test_exec_and_wait() {
#ifdef STATICLIB_WINDOWS
    sl::utils::exec_and_wait("c:/windows/system32/ipconfig", {"/all"}, "ipconfig_wait_out.txt");
#else
    sl::utils::exec_and_wait("/bin/ls", {"-l", "-a", "-h"}, "ls_async_out.txt");
#endif // STATICLIB_WINDOWS
}

void test_executable_path() {
    auto st = sl::utils::current_executable_path();
    slassert(st.length() > 0);
    slassert(st.length() == strlen(st.c_str()));
//    std::cout << "[" << st << "]" << std::endl;
}

void test_current_process_pid() {
    slassert(sl::utils::current_process_pid() > 0);
}

void test_kill_process() {
#ifdef STATICLIB_WINDOWS
    auto exec = std::string("c:/windows/system32/ping");
#else
    auto exec = std::string("/bin/ping");
#endif // STATICLIB_WINDOWS
    auto pid = sl::utils::exec_async(exec, {"127.0.0.1"}, "test_kill_out.txt");
    std::this_thread::sleep_for(std::chrono::seconds(5));
    auto err = sl::utils::kill_process(pid);
    slassert(err.empty());
}

int main() {
    try {
        test_shell_exec();
        //    async logic is not clear in mass test run
        //    test_exec_async();
        test_exec_and_wait();
        test_executable_path();
        test_current_process_pid();
        //  too slow
        // test_kill_process();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}
