/* 
 * File:   process_utils_test.cpp
 * Author: alex
 *
 * Created on September 21, 2015, 8:53 AM
 */

#include <vector>
#include <string>

#include "staticlib/utils/process_utils.hpp"

namespace { // anonymous

namespace su = staticlib::utils;

void test_shell_exec() {
    su::shell_exec_and_wait("echo aaa > echo_out.txt");
}

void test_exec_async() {
    su::exec_async("/bin/ls", {"-l", "-a", "-h"},"ls_async_out.txt");
}

void test_exec_and_wait() {
    su::exec_and_wait("/bin/ls", {"-l", "-a", "-h"}, "ls_wait_out.txt");
}

} // namespace

int main() {
    test_shell_exec();
    test_exec_async();
    test_exec_and_wait();
    
    return 0;
}

