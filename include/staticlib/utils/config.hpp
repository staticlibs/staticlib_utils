/*
 * Copyright 2015, alex at staticlibs.net
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/* 
 * File:   config.hpp
 * Author: alex
 *
 * Created on January 29, 2015, 12:16 PM
 */

#ifndef STATICLIB_CONFIG_HPP
#define	STATICLIB_CONFIG_HPP

// http://stackoverflow.com/a/18387764/314015
#ifndef _MSC_VER
#define STATICLIB_NOEXCEPT noexcept
#define STATICLIB_NOEXCEPT_FALSE noexcept(false)
#else
#define STATICLIB_NOEXCEPT
#define STATICLIB_NOEXCEPT_FALSE
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

// http://stackoverflow.com/a/5920028/314015
#ifdef _WIN32
#define STATICLIB_WINDOWS
#elif __APPLE__
    #include "TargetConditionals.h"
    #if TARGET_IPHONE_SIMULATOR
    #define STATICLIB_IOS
    #elif TARGET_OS_IPHONE
    #define STATICLIB_IOS
    #elif TARGET_OS_MAC
    #define STATICLIB_MAC
    #endif
#elif __linux
#define STATICLIB_LINUX
#elif __ANDROID__
#define STATICLIB_ANDROID
#endif

#endif	/* STATICLIB_CONFIG_HPP */

