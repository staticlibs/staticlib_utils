/* 
 * File:   make_unique.hpp
 * Author: alex
 *
 * Created on January 2, 2015, 1:05 PM
 */

#ifndef MAKE_UNIQUE_HPP
#define	MAKE_UNIQUE_HPP

#include <memory>

namespace staticlib {
namespace stdlib {

// http://herbsutter.com/gotw/_102/
template<typename T, typename ...Args>
std::unique_ptr<T> make_unique(Args&& ...args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

}
} // namespace

#endif	/* MAKE_UNIQUE_HPP */

