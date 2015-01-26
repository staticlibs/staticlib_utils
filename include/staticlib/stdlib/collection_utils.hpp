/* 
 * File:   collection_utils.hpp
 * Author: alex
 *
 * Created on January 25, 2015, 11:00 PM
 */

#ifndef COLLECTION_UTILS_HPP
#define	COLLECTION_UTILS_HPP

#include <vector>
#include <iterator>

/* to include boost::range into client code use the following snippet:
// http://stackoverflow.com/q/11872558/314015
#define BOOST_RESULT_OF_USE_DECLTYPE 1
#include <boost/range/adaptor/transformed.hpp>
#include <boost/range/adaptor/filtered.hpp>
*/

namespace staticlib {
namespace stdlib {

/**
 * Moves all the elements from specified range into vector using 'emplace_back'
 * 
 * @param range range with MoveConstructible elements
 * @return vector containing all element from specified range
 */
// todo: test I am still lazy with value argument
template <typename R>
auto emplace_to_vector(R&& range) -> std::vector<typename std::iterator_traits<decltype(range.begin())>::value_type> {
    auto res = std::vector<typename std::iterator_traits < decltype(range.begin())>::value_type>{};
    // resize is not used here, as neither 'transformed' nor 'filtered' 
    // range will have O(1) size available, and boost::size/std::distance
    // can break stateful one pass ranges; `emplace_to` with explicit resize can be used instead
    // the following will segfault with 'transformed' and lambda
    // res.insert(res.end(), std::make_move_iterator(range.begin()), std::make_move_iterator(range.end()));
    for (auto&& el : range) {
        res.emplace_back(std::move(el));
    }
    return res;
}

/**
 * Moves all the elements from specified range into specified destination
 * using 'emplace_back'.
 * 
 * @param dest destination container
 * @param range source range
 * @return destination container
 */
template <typename T, typename R>
T& emplace_to(T& dest, R&& range) {
    for (auto&& el : range) {
        dest.emplace_back(std::move(el));
    }
    return dest;
}

}
} // namespace

#endif	/* COLLECTION_UTILS_HPP */

