/* 
 * File:   BaseException.cpp
 * Author: alex
 * 
 * Created on January 2, 2015, 12:03 PM
 */

#include "staticlib/stdlib/config.hpp"
#include "staticlib/stdlib/BaseException.hpp"

namespace staticlib {
namespace stdlib {

BaseException::BaseException(std::string msg) : message(msg) { }

const char* BaseException::what() const STATICLIB_NOEXCEPT {
    return message.c_str();
}

}
} //namespace
