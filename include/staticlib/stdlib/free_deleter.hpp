/* 
 * File:   free_deleter.hpp
 * Author: alex
 *
 * Created on January 2, 2015, 2:34 PM
 */

#ifndef FREE_DELETER_HPP
#define	FREE_DELETER_HPP

#include <cstdlib>

namespace staticlib {
namespace stdlib {

template <typename T>
class free_deleter {
public:
    void operator()(T* t) {
        free(t);
    }
};

}
} // namespace

#endif	/* FREE_DELETER_HPP */

