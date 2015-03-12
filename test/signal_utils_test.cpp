/* 
 * File:   signal_utils_test.cpp
 * Author: alex
 *
 * Created on March 12, 2015, 9:38 PM
 */

#include <iostream>
#include <thread>
#include <atomic>
#include <iostream>
#include <cassert>

#include "staticlib/utils/signal_utils.hpp"

namespace su = staticlib::utils;

int main() {
    std::atomic_flag flag = ATOMIC_FLAG_INIT;
    su::initialize_signals();
    su::register_signal_listener([&flag]{
        flag.test_and_set();
    });
    auto th = std::thread{[] {
        std::this_thread::sleep_for(std::chrono::seconds{1});
        su::fire_signal();
    }};
    th.detach();
    su::wait_for_signal();
    std::cout << "signal_utils_test: reached" << std::endl;
    assert(flag.test_and_set());
    
    return 0;
}

