/* 
 * File:   UtilsException.hpp
 * Author: alex
 *
 * Created on January 13, 2015, 9:36 PM
 */

#ifndef STATICLIB_UTILSEXCEPTION_HPP
#define	STATICLIB_UTILSEXCEPTION_HPP

#include "staticlib/utils/BaseException.hpp"

namespace staticlib {
namespace utils {

/**
 * Module specific exception
 */
class UtilsException : public BaseException {
public:
    /**
     * Default constructor
     */
    UtilsException() = default;

    /**
     * Constructor with message
     * 
     * @param msg error message
     */
    UtilsException(const std::string& msg) :
    BaseException(msg) { }

};

}
} //namespace

#endif	/* STATICLIB_UTILSEXCEPTION_HPP */

