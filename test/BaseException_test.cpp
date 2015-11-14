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
 * File:   BaseException_test.cpp
 * Author: alex
 * 
 * Created on January 2, 2015, 12:04 PM
 */

#include <string>
#include <iostream>

#include "staticlib/utils/assert.hpp"
#include "staticlib/utils/tracemsg.hpp"
#include "staticlib/utils/BaseException.hpp"

namespace ss = staticlib::utils;

class TestExc : public ss::BaseException {
public:
    TestExc() = default;
    
    TestExc(const std::string& msg) : 
    ss::BaseException(msg) { }
};

void test_throw() {
    std::string msg{"foo"};
    std::string msgbytes{msg};
    bool catched = false;
    try {
        throw TestExc(msg);
    } catch (const std::exception& e) {
        catched = true;
        slassert(msgbytes == e.what());
    }
    slassert(catched);
}

namespace some_fancy {
namespace some_fancy2 {

void fun_throw() {
    throw ss::BaseException(TRACEMSG("Error happened here!"));
}

void fun1() {
    try {
        fun_throw();
    } catch(const std::exception& e) {
        throw ss::BaseException(TRACEMSG(e.what()));
    }
}

class Thrower {
public:

    void rethrow_some_exception(int foo, std::string bar) {
        (void) foo;
        (void) bar;
        try {
            fun1();
        } catch (const std::exception& e) {
            throw ss::BaseException(TRACEMSG(e.what()));
        }
    }
};


void fun2() {
    try {
        Thrower().rethrow_some_exception(42, "");
    } catch (const std::exception& e) {
        throw ss::BaseException(TRACEMSG(std::string(e.what())
                .append("\nI've caught and rethrow it!")));
    }
}

void fun3() {
    try {
        fun2();
    } catch (const std::exception& e) {
        throw ss::BaseException(TRACEMSG(e.what()));
    }
}
// note: assert here is sensible to line numbers
void test_stacktrace() {
    std::string expected{
R"(Error happened here!
    at some_fancy::some_fancy2::fun_throw(BaseException_test.cpp:46)
    at some_fancy::some_fancy2::fun1(BaseException_test.cpp:53)
    at some_fancy::some_fancy2::Thrower::rethrow_some_exception(BaseException_test.cpp:66)
I've caught and rethrow it!
    at some_fancy::some_fancy2::fun2(BaseException_test.cpp:77)
    at some_fancy::some_fancy2::fun3(BaseException_test.cpp:85))"};
    bool catched = false;
    try {
        fun3();
    } catch (const std::exception& e) {        
        (void) e; catched = true;
        //assert(expected == e.what());
    }
    slassert(catched);
}

} // namespace
} 

void run_tests() {
    test_throw();
    some_fancy::some_fancy2::test_stacktrace();
}

int main() {
    try {
        run_tests();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    } 
    return 0;
}

