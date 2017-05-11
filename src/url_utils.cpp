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
 * File:   url_utils.cpp
 * Author: alex
 *
 * Created on May 11, 2017, 10:55 PM
 */

#include "staticlib/utils/url_utils.hpp"

#include <cstdio>
#include <cstdlib>

namespace staticlib {
namespace utils {

std::string url_decode(const std::string& str) {
    char decode_buf[3];
    std::string result;
    result.reserve(str.size());

    for (std::string::size_type pos = 0; pos < str.size(); ++pos) {
        switch (str[pos]) {
        case '+':
            // convert to space character
            result += ' ';
            break;
        case '%':
            // decode hexadecimal value
            if (pos + 2 < str.size()) {
                decode_buf[0] = str[++pos];
                decode_buf[1] = str[++pos];
                decode_buf[2] = '\0';

                char decoded_char = static_cast<char> (std::strtol(decode_buf, 0, 16));

                // decoded_char will be '\0' if strtol can't parse decode_buf as hex
                // (or if decode_buf == "00", which is also not valid).
                // In this case, recover from error by not decoding.
                if (decoded_char == '\0') {
                    result += '%';
                    pos -= 2;
                } else
                    result += decoded_char;
            } else {
                // recover from error by not decoding character
                result += '%';
            }
            break;
        default:
            // character does not need to be escaped
            result += str[pos];
        }
    };

    return result;
}

std::string url_encode(const std::string& str) {
    char encode_buf[4];
    std::string result;
    encode_buf[0] = '%';
    result.reserve(str.size());

    // character selection for this algorithm is based on the following url:
    // http://www.blooberry.com/indexdot/html/topics/urlencoding.htm
    for (std::string::size_type pos = 0; pos < str.size(); ++pos) {
        switch (str[pos]) {
        default:
            if (str[pos] > 32 && str[pos] < 127) {
                // character does not need to be escaped
                result += str[pos];
                break;
            }
            // else pass through to next case
        case ' ':
        case '$': case '&': case '+': case ',': case '/': case ':':
        case ';': case '=': case '?': case '@': case '"': case '<':
        case '>': case '#': case '%': case '{': case '}': case '|':
        case '\\': case '^': case '~': case '[': case ']': case '`':
            // the character needs to be encoded
            std::sprintf(encode_buf + 1, "%.2X", (unsigned char) (str[pos]));
            result += encode_buf;
            break;
        }
    };

    return result;
}

} // namespace
}
