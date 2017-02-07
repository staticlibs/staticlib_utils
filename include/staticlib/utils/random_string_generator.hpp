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
 * File:   random_string_generator.hpp
 * Author: alex
 *
 * Created on July 2, 2015, 11:27 PM
 */

#ifndef STATICLIB_UTILS_RANDOM_STRING_GENERATOR_HPP
#define	STATICLIB_UTILS_RANDOM_STRING_GENERATOR_HPP

#include <string>
#include <random>
#include <cstdint>

#include "staticlib/utils/utils_exception.hpp"

namespace staticlib {
namespace utils {

/**
 * String generator, uses Mersenne Twister algorithm and alpha-numeric
 * ASCII character set by default. Not thread-safe.
 */
class random_string_generator {
    std::string charset;
    std::mt19937 engine;
    std::uniform_int_distribution<size_t> dist;
            
public:

    /**
     * Deleted copy-constructor
     * 
     * @param other instance
     */
    random_string_generator(const random_string_generator&) = delete;

    /**
     * Deleted copy-assignment operator
     * 
     * @param other instance
     * @return self instance
     */
    random_string_generator& operator=(const random_string_generator&) = delete;
    
    /**
     * Move-constructor
     * 
     * @param other other instance
     */
    random_string_generator(random_string_generator&& other);

    /**
     * Move-assignment operator
     * 
     * @param other other instance
     * @return self instance
     */
    random_string_generator& operator=(random_string_generator&& other);
    
    /**
     * Constructor, uses default alpha-numeric ASCII character set
     */
    random_string_generator();
    
    /**
     * Constructor, allows to specify character set,
     * charset must be non-empty
     * 
     * @param charset character set to use for generated strings
     */
    random_string_generator(std::string charset);
    
    /**
     * Generates random string of specified size
     * 
     * @param length string size
     * @return generated string
     */
    std::string generate(uint32_t length);

    /**
     * Changes all characters in specified string with random ones,
     * initial characters are ignored
     * 
     * @param str string to fill
     */
    void generate(std::string& str);
    
};

}
} // namespace

#endif	/* STATICLIB_UTILS_RANDOM_STRING_GENERATOR_HPP */

