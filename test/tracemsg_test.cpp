/* 
 * File:   tracemsg_test.cpp
 * Author: alex
 * 
 * Created on January 2, 2015, 12:04 PM
 */


#include <cassert>
#include <string>
#include <iostream>

#include "staticlib/utils/string_utils.hpp"
#include "staticlib/utils/tracemsg.hpp"

namespace ss = staticlib::utils;

namespace myfancynamespace {

void test() {
    auto line = __LINE__;
    auto msg = TRACEMSG("foo");
    auto expected = std::string("foo\n") 
            .append("    at myfancynamespace::test(tracemsg_test.cpp:")
            .append(ss::to_string(line + 1))
            .append(")");
    assert(expected == msg);
}

} // namespace

int main() {
    myfancynamespace::test();
    return 0;
}

