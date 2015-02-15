/* 
 * File:   BaseException.cpp
 * Author: alex
 * 
 * Created on January 2, 2015, 12:03 PM
 */

#include "staticlib/utils/config.hpp"
#include "staticlib/utils/BaseException.hpp"

namespace staticlib {
namespace utils {

BaseException::BaseException(std::string msg) : message(msg) { }

const char* BaseException::what() const STATICLIB_NOEXCEPT {
    return message.c_str();
}

}
} //namespace
