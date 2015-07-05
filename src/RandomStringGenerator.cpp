/* 
 * File:   RandomStringGenerator.cpp
 * Author: alex
 * 
 * Created on July 3, 2015, 12:09 AM
 */

#include <string>
#include <random>
#include <utility>
#include <cstdint>

#include "staticlib/utils/UtilsException.hpp"
#include "staticlib/utils/tracemsg.hpp"
#include "staticlib/utils/RandomStringGenerator.hpp"

namespace staticlib {
namespace utils {

// see: http://stackoverflow.com/a/9789249/314015

RandomStringGenerator::RandomStringGenerator(RandomStringGenerator&& other) :
charset(std::move(other.charset)),
engine(std::move(other.engine)),
dist(std::move(other.dist)) { }


RandomStringGenerator& RandomStringGenerator::operator=(RandomStringGenerator&& other) {
    this->charset = std::move(other.charset);
    this->engine = std::move(other.engine);
    this->dist = std::move(other.dist);
    return *this;
}

RandomStringGenerator::RandomStringGenerator() :
RandomStringGenerator("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789") { }

RandomStringGenerator::RandomStringGenerator(std::string charset) :
charset(std::move(charset)),
engine(std::random_device{}()),
dist(static_cast<size_t>(0), this->charset.size() - 1) {
    if(this->charset.empty()) throw UtilsException(TRACEMSG("Invalid empty charset specified"));
}


std::string RandomStringGenerator::generate(uint32_t length) {
    std::string res(length, '#');
    generate(res);
    return res;
}

void RandomStringGenerator::generate(std::string& str) {
    for (char& ch : str) {
        ch = charset[dist(engine)];
    } 
}

}
} // namespace
