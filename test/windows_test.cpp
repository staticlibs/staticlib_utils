/* 
 * File:   windows_test.cpp
 * Author: alex
 *
 * Created on March 16, 2015, 10:14 PM
 */

#include "staticlib/utils/config.hpp"
#ifdef STATICLIB_WINDOWS

#include <cassert>
#include <iostream>

#include "staticlib/utils/windows.hpp"

namespace { // anonymous

namespace sw = staticlib::windows;

void test_widen() {
    // hello in russian in utf-8
    std::string src{"\xd0\xbf\xd1\x80\xd0\xb8\xd0\xb2\xd0\xb5\xd1\x82"};
    auto wst = sw::widen(src);
    assert(6 == wst.length());
    auto converted = sw::narrow(wst);
    assert(src == converted);
}

void test_narrow() {
    // hello in russian in utf-16
    std::wstring ws = L"\U0000043f\U00000440\U00000438\U00000432\U00000435\U00000442";
    auto st = sw::narrow(ws);
    assert(12 == st.length());
    auto converted = sw::widen(st);
    assert(ws == converted);
}

void test_errcode_to_string() {
    std::string err0 = sw::errcode_to_string(0);
    assert(0 == err0.length());
    std::string err1 = sw::errcode_to_string(1);
    assert(err1.length() > 0);
    assert(']' == err1[err1.length() - 1]);
    std::string err87 = sw::errcode_to_string(87);
    assert(err87.length() > 0);
    assert(']' == err87[err87.length() - 1]);
}

void test_get_exec_dir() {
    std::cout << sw::get_exec_dir() << std::endl;
}

} // namespace

int main() {
    test_widen();
    test_narrow();
    test_errcode_to_string();
    test_get_exec_dir();

    return 0;
}

#else // STATICLIB_WINDOWS

int main() {
    return 0;
}

#endif // STATICLIB_WINDOWS
