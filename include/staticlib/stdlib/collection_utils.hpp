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

namespace staticlib {
namespace stdlib {

/**
 * Moves all the elements from specified range into vector
 * 
 * @param range range with MoveConstructible elements
 * @return vector containing all element from specified range
 */
template <typename R>
auto move_into_vector(R&& range) -> std::vector<typename std::iterator_traits<decltype(range.begin())>::value_type> {
    auto res = std::vector<typename std::iterator_traits < decltype(range.begin())>::value_type>{};
    for (auto&& el : range) {
        res.emplace_back(std::move(el));
    }
    return res;
}

}
} // namespace

#endif	/* COLLECTION_UTILS_HPP */

