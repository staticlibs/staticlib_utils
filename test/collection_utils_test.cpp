/* 
 * File:   collection_utils_test.cpp
 * Author: alex
 *
 * Created on January 25, 2015, 11:03 PM
 */

#include <cassert>
#include <vector>
#include <string>
#include <iostream>
#include <memory>

// http://stackoverflow.com/q/11872558/314015
#define BOOST_RESULT_OF_USE_DECLTYPE 1
#include <boost/range/adaptor/transformed.hpp>
#include <boost/range/adaptor/filtered.hpp>
#include <boost/range/join.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/move/iterator.hpp>

#include "staticlib/stdlib/collection_utils.hpp"

namespace range = boost::range;
namespace adaptors = boost::adaptors;
namespace ss = staticlib::stdlib;

// unique_ptr used here as noncopyable but moveable objects

void test_transformed() {
    auto vec = std::vector<std::string>{"foo", "bar", "baz"};
    auto range = adaptors::transform(vec, [](const std::string & st) {
        return std::unique_ptr<std::string>(new std::string(st + "_42"));
    });
    auto res = ss::emplace_to_vector(range);

    assert(3 == res.size());
    assert("foo_42" == *res[0]);
    assert("bar_42" == *res[1]);
    assert("baz_42" == *res[2]);    
}

void test_filtered() {
    auto vec = std::vector<std::string>{"foo", "bar", "baz"};
    auto filtered = adaptors::filter(vec, [](const std::string& st) {
        return "foo" != st;
    });
    auto range = adaptors::transform(filtered, [](const std::string & st) {
        return std::unique_ptr<std::string>(new std::string(st.c_str()));
    });
    auto res = ss::emplace_to_vector(range);

    assert(2 == res.size());
    assert("bar" == *res[0]);
    assert("baz" == *res[1]);    
    
}

void test_vector() {
    auto vec = std::vector<std::string>{"foo", "bar", "baz"};
    auto res = ss::emplace_to_vector(vec);

    assert(3 == res.size());
    assert("foo" == res[0]);
    assert("bar" == res[1]);
    assert("baz" == res[2]);    
}

void test_emplate_to() {
    auto vec = std::vector<std::string>{"foo", "bar", "baz"};
    auto range = adaptors::transform(vec, [](const std::string & st) {
        return std::unique_ptr<std::string>(new std::string(st + "_42"));
    });
    auto dest = std::vector<std::unique_ptr<std::string>>();
    dest.reserve(vec.size());
    ss::emplace_to(dest, range);

    assert(3 == dest.size());
    assert("foo_42" == *dest[0]);
    assert("bar_42" == *dest[1]);
    assert("baz_42" == *dest[2]);   
}

void test_join() {
//    auto vec1 = std::vector<std::unique_ptr<std::string>>{};
//    vec1.emplace_back(new std::string("40"));
//    vec1.emplace_back(new std::string("41"));
//    vec1.emplace_back(new std::string("42"));
//
//    auto vec2 = std::vector<std::unique_ptr <std::string>>{};
//    vec2.emplace_back(new std::string("43"));
//    vec2.emplace_back(new std::string("44"));

//    auto joined_vectors1 = range::join(vec1, vec2);
//    for (auto it = joined_vectors1.begin(); it != joined_vectors1.end(); ++it) {
//        auto el = std::move(*it);
//        std::cout << *el << std::endl;
//    }
//
//    auto joined_vectors2 = range::join(vec1, vec2);
//    for (auto it = joined_vectors2.begin(); it != joined_vectors2.end(); ++it) {
//        auto el = std::move(*it);
//        std::cout << *el << std::endl;
//    }

    
    
//    auto range1 = adaptors::transform(vec1, [](std::unique_ptr<std::string>& st) {
//        auto res = std::move(st);
//        res->append("_1");
//        return res;
//    }); 
    
//    auto range1_filtered = adaptors::filter(range1, [](std::unique_ptr<std::string>& st) {
//        return "40_1" != (*st);
//    });

//    auto range2 = adaptors::transform(vec2, [](std::unique_ptr<std::string>& st) {
//        auto res = std::move(st);
//        res->append("_2");
//        return res;
//    });
//
//    auto r1 = boost::make_iterator_range(boost::make_move_iterator(range1.begin()), boost::make_move_iterator(range1.end()));
//    auto r2 = boost::make_iterator_range(boost::make_move_iterator(range2.begin()), boost::make_move_iterator(range2.end()));
//    auto joined_ranges = range::join(r1, r2);
//    for (auto&& it = joined_ranges.begin(); it != joined_ranges.end(); ++it) {
//        auto el = std::move(*it);
//        std::cout << *el << std::endl;
//    }
    

//    auto it = joined_ranges.begin();
//    auto end = joined_ranges.end();
//    for (auto i = 0; it + i != end; i++) {
//        auto el = std::move(*(it + i));
//        std::cout << *el << std::endl;
//    }
    
//    std::cout << *el1 << std::endl;
//    auto el2 = std::move(*(it + 1));
    
    
//    for (auto&& it = joined_ranges.begin(); it != joined_ranges.end(); ++it) {
//        auto el = std::move(*it);
//        std::cout << *el << std::endl;
//    }
    
//    for(auto&& el : joined_ranges) {
//        std::cout << *el << std::endl;
//    }
}

int main() {
    test_transformed();
    test_filtered();
    test_vector();
    test_emplate_to();
    test_join();

    return 0;
}

