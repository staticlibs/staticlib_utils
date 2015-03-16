/* 
 * File:   windows.hpp
 * Author: alex
 *
 * Created on March 16, 2015, 9:53 PM
 */

#ifndef STATICLIB_WINDOWS_HPP
#define	STATICLIB_WINDOWS_HPP

#include <string>
#include <cstdint>

#include "staticlib/utils/config.hpp"

namespace staticlib {
namespace utils {

/**
 * Convert string from UTF-8 multibyte to UTF-16 widechar
 * 
 * @param st UTF-8 multibyte string
 * @return UTF-16 wide string
 */
std::wstring widen(const std::string& st);

/**
 * Convert string from UTF-16 widechar to UTF-8 multibyte
 * 
 * @param wstring UTF-16 wide string
 * @return UTF-8 multibyte string
 */
std::string narrow(std::wstring wstr);

/**
 * Convert buffer from UTF-16 widechar to UTF-8 multibyte
 * 
 * @param wbuf UTF-16 widechar buffer
 * @param length buffer length in wide chars
 * @return UTF-8 multibyte string
 */
std::string narrow(const wchar_t* wbuf, size_t length);

/**
 * Convert Windows system error code (http://msdn.microsoft.com/en-us/library/windows/desktop/ms681381%28v=vs.85%29.aspx)
 * to english message
 * 
 * @param code error code
 * @return message in english
 */
std::string errcode_to_string(uint32_t code) STATICLIB_NOEXCEPT;

/**
 * Returns the directory where current executable resides
 * 
 * @return directory path in UTF-8
 */
std::string get_exec_dir();

} //namespace
}

#endif	/* STATICLIB_WINDOWS_HPP */

