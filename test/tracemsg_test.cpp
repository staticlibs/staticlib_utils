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
 * File:   tracemsg_test.cpp
 * Author: alex
 * 
 * Created on January 2, 2015, 12:04 PM
 */


#include <string>
#include <iostream>

#include "staticlib/utils/assert.hpp"

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
    slassert(expected == msg);
}

} // namespace

int main() {
    try {
        myfancynamespace::test();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}

