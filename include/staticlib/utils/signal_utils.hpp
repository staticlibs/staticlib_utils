/* 
 * File:   signal_utils.hpp
 * Author: alex
 *
 * Created on March 12, 2015, 8:21 PM
 */

#ifndef STATICLIB_SIGNAL_UTILS_HPP
#define	STATICLIB_SIGNAL_UTILS_HPP

#include <functional>

namespace staticlib {
namespace utils {

/**
 * Initializes signal handlers to be used with 'wait_for_signal'.
 * Should be called only once.
 */
void initialize_signals();

/**
 * Registers listener for SIGINT/SIGTERM
 * (or CTRL_C_EVENT/CTRL_BREAK_EVENT/CTRL_CLOSE_EVENT/CTRL_SHUTDOWN_EVENT on Windows)
 * 
 * @param listener listener function (lambda)
 */
void register_signal_listener(std::function<void(void)> listener);

/*
 * Blocks current thread until the SIGINT/SIGTERM
 * signal will be received by this process.
 * Do not uses locks, uses 'atomic_flag' and 'sleep_for' instead
 * (so 100-200 ms timeout is expected after signal receiving).
 */
void wait_for_signal();

/**
 * Emulates receiving SIGINT/SIGTERM for this process
 */
void fire_signal();

} // namespace
}

#endif	/* STATICLIB_SIGNAL_UTILS_HPP */

