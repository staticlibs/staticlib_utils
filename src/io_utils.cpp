/* 
 * File:   io_utils.cpp
 * Author: alex
 * 
 * Created on April 6, 2015, 7:36 PM
 */

#include <istream>
#include <ostream>
#include <string>
#include <array>
#include <streambuf>

#include "staticlib/utils/string_utils.hpp"
#include "staticlib/utils/tracemsg.hpp"
#include "staticlib/utils/UtilsException.hpp"

#include "staticlib/utils/io_utils.hpp"

namespace staticlib {
namespace utils {

void write_all(std::streambuf& sink, const char* buf, std::streamsize buflen) {
    std::streamsize result = 0;
    while (result < buflen) {
        std::streamsize amt = sink.sputn(buf + result, buflen - result);
        result += amt;
    }
}

void write_all(std::streambuf& sink, const std::string& str) {
    write_all(sink, str.c_str(), static_cast<std::streamsize> (str.length()));
}

std::streamsize read_all(std::streambuf& src, char* buf, std::streamsize buflen) {
    std::streamsize result = 0;
    while (result < buflen) {
        std::streamsize amt = src.sgetn(buf + result, buflen - result);
        if (0 == amt && std::char_traits<char>::eof() == src.sbumpc()) break;
        result += amt;        
    }
    return result;
}

void read_exact(std::streambuf& src, char* buf, std::streamsize buflen) {
    auto res = read_all(src, buf, buflen);
    if (res != buflen) throw UtilsException(TRACEMSG(
            std::string("Read amount: [" + to_string(res) + "]" +
            " of expected: [" + to_string(buflen) + "]")));
}

std::streamsize copy_all(std::streambuf& src, std::streambuf& sink, char* buf, std::streamsize buflen) {
    std::streamsize result = 0;
    std::streamsize amt;
    while (buflen == (amt = read_all(src, buf, buflen))) {
        write_all(sink, buf, amt);
        result += amt;
    }
    // tail
    if (amt > 0) {
        write_all(sink, buf, amt);
        result += amt;
    }
    return result;
}


} // namespace
}
