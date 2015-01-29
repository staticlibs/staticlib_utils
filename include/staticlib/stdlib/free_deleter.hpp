/* 
 * File:   free_deleter.hpp
 * Author: alex
 *
 * Created on January 2, 2015, 2:34 PM
 */

#ifndef STATICLIB_FREE_DELETER_HPP
#define	STATICLIB_FREE_DELETER_HPP

#include <cstdlib>

namespace staticlib {
namespace stdlib {

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

#endif	/* STATICLIB_FREE_DELETER_HPP */

