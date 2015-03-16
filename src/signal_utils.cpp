/* 
 * File:   signal_utils.cpp
 * Author: alex
 * 
 * Created on March 12, 2015, 8:49 PM
 */

#include <functional>
#include <atomic>
#include <vector>
#include <thread>

#include <signal.h>

#include "staticlib/utils/config.hpp"
#ifdef STATICLIB_WINDOWS
#include <windows.h>
#endif // STATICLIB_WINDOWS

#include "staticlib/utils/UtilsException.hpp"
#include "staticlib/utils/signal_utils.hpp"

namespace staticlib {
namespace utils {

namespace { // anonymous

std::vector<std::function<void(void)>>& get_static_liteners() {
    static std::vector<std::function<void(void)>> vec{};
    return vec;
} 

std::atomic_flag& get_static_flag() {
    static std::atomic_flag flag = ATOMIC_FLAG_INIT;
    return flag;
}

void handler_internal() {
    for (std::function<void(void)> fu : get_static_liteners()) {
        fu();
    }
    get_static_flag().clear();
}

#ifdef STATICLIB_WINDOWS

BOOL WINAPI handler_platform(DWORD ctrl_type) {
    switch (ctrl_type) {
    case CTRL_C_EVENT:
    case CTRL_BREAK_EVENT:
    case CTRL_CLOSE_EVENT:
    case CTRL_SHUTDOWN_EVENT:
        handler_internal();
        return TRUE;
    default:
        return FALSE;
    }
}

void initialize_signals_platform() {
    SetConsoleCtrlHandler(handler_platform, TRUE);
}

#else // STATICLIB_WINDOWS

void handler_platform(int sig) {
    (void) sig;
    handler_internal();
}

void initialize_signals_platform() {
    signal(SIGINT, handler_platform);
    signal(SIGTERM, handler_platform);
}

#endif // STATICLIB_WINDOWS

} // namespace

void initialize_signals() {
    auto prev = get_static_flag().test_and_set();
    if (prev) throw UtilsException("Signal listeners initialization error");
    initialize_signals_platform();
}

void register_signal_listener(std::function<void(void)> listener) {
    get_static_liteners().emplace_back(std::move(listener));
}

// can be done without sleep using semaphore
void wait_for_signal() {
    auto timeout = std::chrono::milliseconds{200};
    while(get_static_flag().test_and_set()) {
        std::this_thread::sleep_for(timeout);
    }
    get_static_flag().clear();
}

void fire_signal() {
    handler_internal();
}

} // namespace
}

