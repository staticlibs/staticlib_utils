/* 
 * File:   string_utils.hpp
 * Author: alex
 *
 * Created on January 2, 2015, 12:59 PM
 */

#ifndef STATICLIB_TO_STRING_HPP
#define	STATICLIB_TO_STRING_HPP

#include <string>
#include <sstream>
#include <typeinfo>

#include "staticlib/stdlib/config.hpp"
#include "staticlib/stdlib/tracemsg.hpp"
#include "staticlib/stdlib/StdlibException.hpp"

namespace staticlib {
namespace stdlib {

/**
 * Generic `to_string` implementation, already exists as `std::to_string`
 * in most C++11 compilers except GCC 4.8
 * 
 * @param t value to stringify
 * @return string representation of specified value
 */
template<typename T>
std::string to_string(T t) {
    try {
        std::stringstream ss{};
        ss << t;
        return ss.str();
    } catch (const std::exception& e) {
        std::string tname{typeid (t).name()};
        throw StdlibException(TRACEMSG(std::string(e.what()) + 
                "\nError stringifying object, type: [" + tname + "]"));
    }
}

/**
 * Access underlying string buffer as writable char array safely (according to C++11)
 * Will resize specified string (memory will be default-initialized).
 * 
 * @param str string instance
 * @param required_size required size of the buffer, string will be resized to this size
 * @return writable buffer owned by the specified string
 */
char* get_buffer(std::string& str, std::string::size_type required_size);

/**
 * Access underlying wide string buffer as writable char array safely (according to C++11)
 * Will resize specified string (memory will be default-initialized).
 * 
 * @param str wide string instance
 * @param required_size required size of the buffer, string will be resized to this size
 * @return writable buffer owned by the specified string
 */
wchar_t* get_buffer(std::wstring& str, std::wstring::size_type required_size);

/**
 * Allocates a buffer and copies there contents of the string.
 * Allocated buffer must be freed by the caller.
 * 
 * @param str string to copy
 * @return allocated buffer
 */
char* alloc_copy(const std::string& str) STATICLIB_NOEXCEPT;

}
} // namespace

#endif	/* STATICLIB_TO_STRING_HPP */

