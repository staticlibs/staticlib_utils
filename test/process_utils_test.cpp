/* 
 * File:   process_utils_test.cpp
 * Author: alex
 *
 * Created on September 21, 2015, 8:53 AM
 */

#include <vector>
#include <string>
#include <iostream>

#include "staticlib/utils/config.hpp"
#include "staticlib/utils/process_utils.hpp"

namespace { // anonymous

namespace su = staticlib::utils;

void test_shell_exec() {
    su::shell_exec_and_wait("echo aaa > echo_out.txt");
}

void test_exec_async() {
#ifdef STATICLIB_WINDOWS
    su::exec_async("c:/windows/system32/ipconfig", {"/all"}, "ipconfig_async_out.txt");
#else
    su::exec_async("/bin/ls", {"-l", "-a", "-h"}, "ls_async_out.txt");
#endif // STATICLIB_WINDOWS
}

void test_exec_and_wait() {
#ifdef STATICLIB_WINDOWS
    su::exec_and_wait("c:/windows/system32/ipconfig", {"/all"}, "ipconfig_wait_out.txt");
#else
    su::exec_and_wait("/bin/ls", {"-l", "-a", "-h"}, "ls_async_out.txt");
#endif // STATICLIB_WINDOWS
}

} // namespace

int main() {
    test_shell_exec();
    test_exec_async();
    test_exec_and_wait();
    
    return 0;
}

