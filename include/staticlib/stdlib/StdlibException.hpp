/* 
 * File:   StdlibException.hpp
 * Author: alex
 *
 * Created on January 13, 2015, 9:36 PM
 */

#ifndef STATICLIB_STDLIBEXCEPTION_HPP
#define	STATICLIB_STDLIBEXCEPTION_HPP

#include "staticlib/stdlib/BaseException.hpp"

namespace staticlib {
namespace stdlib {

/**
 * Module specific exception
 */
class StdlibException : public BaseException {
public:
    /**
     * Default constructor
     */
    StdlibException() = default;

    /**
     * Constructor with message
     * 
     * @param msg error message
     */
    StdlibException(const std::string& msg) :
    BaseException(msg) { }

};

}
} //namespace

#endif	/* STATICLIB_STDLIBEXCEPTION_HPP */

