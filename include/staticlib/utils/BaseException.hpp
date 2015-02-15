/* 
 * File:   StaticlibException.hpp
 * Author: alex
 *
 * Created on January 2, 2015, 11:49 AM
 */

#ifndef STATICLIB_BASEEXCEPTION_HPP
#define	STATICLIB_BASEEXCEPTION_HPP

#include <string>
#include <exception>

#include "staticlib/utils/config.hpp"

namespace staticlib {
namespace utils {

/**
 * Base exception class for business exceptions in staticlib modules
 */
class BaseException : public std::exception {
protected:
    /**
     * Error message
     */
    std::string message;

public:
    /**
     * Default constructor
     */
    BaseException() = default;
    
    /**
     * Constructor with message
     * 
     * @param msg error message
     */
    BaseException(std::string msg);
    
    /**
     * Returns error message
     * 
     * @return error message
     */
    virtual const char* what() const STATICLIB_NOEXCEPT;
};

}
} //namespace

#endif	/* STATICLIB_BASEEXCEPTION_HPP */

