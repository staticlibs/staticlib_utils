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
 * File:   windows_test.cpp
 * Author: alex
 *
 * Created on March 16, 2015, 10:14 PM
 */

#include "staticlib/config.hpp"
#ifdef STATICLIB_WINDOWS

#include "staticlib/utils/windows.hpp"

#include <iostream>

#include "staticlib/config/assert.hpp"

void test_widen() {
    // hello in russian in utf-8
    std::string src{"\xd0\xbf\xd1\x80\xd0\xb8\xd0\xb2\xd0\xb5\xd1\x82"};
    auto wst = sl::utils::widen(src);
    slassert(6 == wst.length());
    auto converted = sl::utils::narrow(wst);
    slassert(src == converted);
}

void test_narrow() {
    // hello in russian in utf-16
    std::wstring ws = L"\U0000043f\U00000440\U00000438\U00000432\U00000435\U00000442";
    auto st = sl::utils::narrow(ws);
    slassert(12 == st.length());
    auto converted = sl::utils::widen(st);
    slassert(ws == converted);
}

void test_errcode_to_string() {
    std::string err0 = sl::utils::errcode_to_string(0);
    slassert(0 == err0.length());
    std::string err1 = sl::utils::errcode_to_string(1);
    slassert(err1.length() > 0);
    slassert(']' == err1[err1.length() - 1]);
    std::string err87 = sl::utils::errcode_to_string(87);
    slassert(err87.length() > 0);
    slassert(']' == err87[err87.length() - 1]);
}

int main() {
    try {
        test_widen();
        test_narrow();
        test_errcode_to_string();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}

#else // STATICLIB_WINDOWS

int main() {
    return 0;
}

#endif // STATICLIB_WINDOWS
