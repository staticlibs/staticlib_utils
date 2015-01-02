/* 
 * File:   free_deleter_test.cpp
 * Author: alex
 *
 * Created on January 2, 2015, 2:38 PM
 */

#include <cassert>
#include <memory>

#include "staticlib/stdlib/free_deleter.hpp"

namespace ss = staticlib::stdlib;

int main() {

    char* ptr = static_cast<char*>(malloc(42));
    std::unique_ptr<char, ss::free_deleter<char>> uptr{ptr, ss::free_deleter<char>()};
    (void) uptr; 
    // memory will be freed on scope exit
    return 0;
}

