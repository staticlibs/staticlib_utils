/* 
 * File:   memory_utils_test.cpp
 * Author: alex
 *
 * Created on January 2, 2015, 1:07 PM
 */

#include <cassert>
#include <string>

#include "staticlib/utils/memory_utils.hpp"

namespace { // anonymous

namespace ss = staticlib::utils;

void test_make_unique() {
    auto ptr = ss::make_unique<std::string>("42");
    assert("42" == *ptr.get());
}

void test_free_deleter() {
    char* ptr = static_cast<char*> (malloc(42));
    std::unique_ptr<char, ss::free_deleter<char>> uptr{ptr, ss::free_deleter<char>()};
    (void) uptr;
    // memory will be freed on scope exit
}

} // namespace



int main() {
    test_make_unique();
    test_free_deleter();

    
    return 0;
}

