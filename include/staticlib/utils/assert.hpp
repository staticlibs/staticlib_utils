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
 * File:   assert.hpp
 * Author: alex
 *
 * Created on November 14, 2015, 1:03 PM
 */

#ifndef STATICLIB_ASSERT_HPP
#define	STATICLIB_ASSERT_HPP

#include <string>

#include "staticlib/utils/BaseException.hpp"
#include "staticlib/utils/tracemsg.hpp"

/**
 * Assert macro, will throw `AssertException` on expression fail
 */
#define slassert(_expr) if (!(_expr)) throw staticlib::utils::AssertException(TRACEMSG("ASSERTION ERROR"));

namespace staticlib {
namespace utils {

/**
 * Assert-specific exception
 */
class AssertException : public BaseException {
public:
    /**
     * Default constructor
     */
    AssertException() = default;

    /**
     * Constructor with message
     * 
     * @param msg error message
     */
    AssertException(const std::string& msg) :
    BaseException(msg) { }

};

}
}

#endif	/* STATICLIB_ASSERT_HPP */

