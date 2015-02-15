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

