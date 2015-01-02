/* 
 * File:   to_string_test.cpp
 * Author: alex
 *
 * Created on January 2, 2015, 1:06 PM
 */

#include <cassert>

#include "staticlib/stdlib/to_string.hpp"

namespace ss = staticlib::stdlib;

int main() {
    assert("42" == ss::to_string(42));
    
    return 0;
}

