/* 
 * File:   process_utils_test.cpp
 * Author: alex
 *
 * Created on September 21, 2015, 8:53 AM
 */

#include "staticlib/utils/process_utils.hpp"

int main() {

    staticlib::utils::shell_exec_and_wait("echo aaa > echo_out.txt");
    
    return 0;
}

