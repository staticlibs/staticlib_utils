/* 
 * File:   parse_int.cpp
 * Author: alex
 * 
 * Created on January 31, 2015, 3:51 PM
 */

#include <cstdlib>
#include <cerrno>
#include <climits>

#include "staticlib/stdlib/StdlibException.hpp"
#include "staticlib/stdlib/tracemsg.hpp"
#include "staticlib/stdlib/parse_int.hpp"

namespace staticlib {
namespace stdlib {

int16_t parse_int16(const std::string& str) {
    auto cstr = str.c_str();
    char* endptr;
    errno = 0;
    long l = std::strtol(cstr, &endptr, 0);
    if (errno == ERANGE || cstr + str.length() != endptr) {
        throw StdlibException(TRACEMSG(std::string("Cannot parse int16_t from string:[" + str + "]")));
    }
    if (l < SHRT_MIN || l > SHRT_MAX) {
        throw StdlibException(TRACEMSG(std::string("Value overflow for int16_t from string:[" + str + "]")));
    }
    return static_cast<int16_t> (l);
}

uint16_t parse_uint16(const std::string& str) {
    auto cstr = str.c_str();
    char* endptr;
    errno = 0;
    long l = std::strtol(cstr, &endptr, 0);
    if (errno == ERANGE || cstr + str.length() != endptr) {
        throw StdlibException(TRACEMSG(std::string("Cannot parse uint16_t from string:[" + str + "]")));
    }
    if (l < 0 || l > USHRT_MAX) {
        throw StdlibException(TRACEMSG(std::string("Value overflow for uint16_t from string:[" + str + "]")));
    }
    return static_cast<uint16_t> (l);
}

int32_t parse_int32(const std::string& str) {
    auto cstr = str.c_str();
    char* endptr;
    errno = 0;
    long l = std::strtol(cstr, &endptr, 0);
    if (errno == ERANGE || cstr + str.length() != endptr) {
        throw StdlibException(TRACEMSG(std::string("Cannot parse int32_t from string:[" + str + "]")));
    }
    if (l < INT_MIN || l > INT_MAX) {
        throw StdlibException(TRACEMSG(std::string("Value overflow for int32_t from string:[" + str + "]")));
    }
    return static_cast<int32_t> (l);
}

uint32_t parse_uint32(const std::string& str) {
    auto cstr = str.c_str();
    char* endptr;
    errno = 0;
    long l = std::strtoll(cstr, &endptr, 0);
    if (errno == ERANGE || cstr + str.length() != endptr) {
        throw StdlibException(TRACEMSG(std::string("Cannot parse uint32_t from string:[" + str + "]")));
    }
    if (l < 0 || l > UINT_MAX) {
        throw StdlibException(TRACEMSG(std::string("Value overflow for uint32_t from string:[" + str + "]")));
    }
    return static_cast<uint32_t> (l);
}

int64_t parse_int64(const std::string& str) {
    auto cstr = str.c_str();
    char* endptr;
    errno = 0;
    long l = std::strtoll(cstr, &endptr, 0);
    if (errno == ERANGE || cstr + str.length() != endptr) {
        throw StdlibException(TRACEMSG(std::string("Cannot parse int64_t from string:[" + str + "]")));
    }
    return static_cast<int64_t> (l);
}

uint64_t parse_uint64(const std::string& str) {
    auto cstr = str.c_str();
    char* endptr;
    errno = 0;
    long l = std::strtoull(cstr, &endptr, 0);
    if (errno == ERANGE || cstr + str.length() != endptr) {
        throw StdlibException(TRACEMSG(std::string("Cannot parse uint64_t from string:[" + str + "]")));
    }
    return static_cast<uint64_t> (l);
}

} // namespace
}
