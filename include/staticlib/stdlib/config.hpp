/* 
 * File:   config.hpp
 * Author: alex
 *
 * Created on January 29, 2015, 12:16 PM
 */

#ifndef CONFIG_HPP
#define	CONFIG_HPP

// http://stackoverflow.com/a/18387764/314015
#ifndef _MSC_VER
#define STATICLIB_NOEXCEPT noexcept
#else
#define STATICLIB_NOEXCEPT
#endif // _MSC_VER

// https://github.com/boostorg/assert/blob/94ebde8bcff31752b7ffe7fcd58ad4d783bf958c/include/boost/current_function.hpp
#if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__)

#define STATICLIB_CURRENT_FUNCTION __PRETTY_FUNCTION__

#elif defined(__DMC__) && (__DMC__ >= 0x810)

#define STATICLIB_CURRENT_FUNCTION __PRETTY_FUNCTION__

#elif defined(__FUNCSIG__)

#define STATICLIB_CURRENT_FUNCTION __FUNCSIG__

#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))

#define STATICLIB_CURRENT_FUNCTION __FUNCTION__

#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)

#define STATICLIB_CURRENT_FUNCTION __FUNC__

#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)

#define STATICLIB_CURRENT_FUNCTION __func__

#elif defined(__cplusplus) && (__cplusplus >= 201103)

#define STATICLIB_CURRENT_FUNCTION __func__

#else

#define STATICLIB_CURRENT_FUNCTION "(unknown)"

#endif


#endif	/* CONFIG_HPP */

