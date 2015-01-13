/* 
 * File:   memory_utils_test.cpp
 * Author: alex
 *
 * Created on January 2, 2015, 1:07 PM
 */

#include <cassert>
#include <string>

#include "staticlib/stdlib/memory_utils.hpp"

namespace ss = staticlib::stdlib;

int main() {

    auto ptr = ss::make_unique<std::string>("42");
    assert("42" == *ptr.get());
    
    return 0;
}

