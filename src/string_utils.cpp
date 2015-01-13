/* 
 * File:   string_utils.cpp
 * Author: alex
 *
 * Created on January 13, 2015, 9:03 PM
 */

#include <string>
#include <exception>

#include "staticlib/stdlib/tracemsg.hpp"
#include "staticlib/stdlib/StdlibException.hpp"
#include "staticlib/stdlib/string_utils.hpp"

namespace staticlib {
namespace stdlib {

namespace { // anonymous

template <typename T>
T* get_buffer_internal(std::basic_string<T>& str, typename std::basic_string<T>::size_type required_size) {
    try {
        str.resize(required_size);
        return &str.front();
    } catch (const std::exception& e) {
        throw StdlibException(TRACEMSG(std::string(e.what()).append("\n")
                .append("Error getting buffer with required size: [")
                .append(to_string(required_size))
                .append("] from string, length: [")
                .append(to_string(str.length()))
                .append("]")));
    }
}

} // namespace

char* get_buffer(std::string& str, std::string::size_type required_size) {
    return get_buffer_internal<char>(str, required_size);
}

wchar_t* get_buffer(std::wstring& str, std::wstring::size_type required_size) {
    return get_buffer_internal<wchar_t>(str, required_size);
}

}
} // namespace

