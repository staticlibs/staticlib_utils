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

int main() {
    try {
        test_shell_exec();
        //    async logic is not clear in mass test run
        //    test_exec_async();
        test_exec_and_wait();
        test_executable_path();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}
