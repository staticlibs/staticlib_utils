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

template<typename T>
std::string to_string(T t) {
    std::stringstream ss;
    ss << t;
    return ss.str();
} 

}
} // namespace

#endif	/* TO_STRING_HPP */

