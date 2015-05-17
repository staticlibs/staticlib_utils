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
 * File:   memory_utils.hpp
 * Author: alex
 *
 * Created on January 2, 2015, 1:05 PM
 */

#ifndef STATICLIB_MEMORY_UTILS_HPP
#define	STATICLIB_MEMORY_UTILS_HPP

#include <memory>

namespace staticlib {
namespace utils {

/**
 * Shortcut template for creating `std::unique_ptr`, 
 * see [details](http://herbsutter.com/gotw/_102/).
 * Will became obsolete in C++14.
 * 
 * @param args pointer object constructor arguments
 * @return smart pointer to created object
 */
template<typename T, typename ...Args>
std::unique_ptr<T> make_unique(Args&& ...args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

/**
 * Deleter implementation for smart pointer classes.
 * Will call 'free' function on the pointer.
 */
template <typename T>
class free_deleter {
public:

    /**
     * Delete operation, will call 'free' function on the pointer.
     * 
     * @param t pointer
     */
    void operator()(T* t) {
        free(t);
    }
};

}
} // namespace

#endif	/* STATICLIB_MEMORY_UTILS_HPP */

