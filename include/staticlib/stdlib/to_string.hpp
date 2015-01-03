/* 
 * File:   to_string.hpp
 * Author: alex
 *
 * Created on January 2, 2015, 12:59 PM
 */

#ifndef TO_STRING_HPP
#define	TO_STRING_HPP

#include <string>
#include <sstream>

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
    std::stringstream ss;
    ss << t;
    return ss.str();
} 

}
} // namespace

#endif	/* TO_STRING_HPP */

