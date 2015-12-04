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
 * File:   RandomStringGenerator.hpp
 * Author: alex
 *
 * Created on July 2, 2015, 11:27 PM
 */

#ifndef STATICLIB_UTILS_RANDOMSTRINGGENERATOR_HPP
#define	STATICLIB_UTILS_RANDOMSTRINGGENERATOR_HPP

#include <string>
#include <random>
#include <cstdint>

#include "staticlib/utils/UtilsException.hpp"

namespace staticlib {
namespace utils {

/**
 * String generator, uses Mersenne Twister algorithm and alpha-numeric
 * ASCII character set by default. Not thread-safe.
 */
class RandomStringGenerator {
    
    std::string charset;
    std::mt19937 engine;
    std::uniform_int_distribution<size_t> dist;
            
public:

    /**
     * Deleted copy-constructor
     * 
     * @param other instance
     */
    RandomStringGenerator(const RandomStringGenerator&) = delete;

    /**
     * Deleted copy-assignment operator
     * 
     * @param other instance
     * @return self instance
     */
    RandomStringGenerator& operator=(const RandomStringGenerator&) = delete;
    
    /**
     * Move-constructor
     * 
     * @param other other instance
     */
    RandomStringGenerator(RandomStringGenerator&& other);

    /**
     * Move-assignment operator
     * 
     * @param other other instance
     * @return self instance
     */
    RandomStringGenerator& operator=(RandomStringGenerator&& other);
    
    /**
     * Constructor, uses default alpha-numeric ASCII character set
     */
    RandomStringGenerator();
    
    /**
     * Constructor, allows to specify character set,
     * charset must be non-empty
     * 
     * @param charset character set to use for generated strings
     */
    RandomStringGenerator(std::string charset);
    
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

#endif	/* STATICLIB_UTILS_RANDOMSTRINGGENERATOR_HPP */

