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

#include "staticlib/stdlib/collection_utils.hpp"

namespace adaptors = boost::adaptors;
namespace ss = staticlib::stdlib;

void test_transformed() {
    auto vec = std::vector<std::string>{"foo", "bar", "baz"};
    auto range = vec | adaptors::transformed([](const std::string & st) {
        return std::unique_ptr<std::string>(new std::string(st + "_42"));
    });
    auto res = ss::move_into_vector(range);

    assert(3 == res.size());
    assert("foo_42" == *res[0]);
    assert("bar_42" == *res[1]);
    assert("baz_42" == *res[2]);    
}

void test_filtered() {
    auto vec = std::vector<std::string>{"foo", "bar", "baz"};
    auto range = vec | adaptors::filtered([](const std::string& st) {
        return "foo" != st;
    }) | adaptors::transformed([](const std::string & st) {
        return std::unique_ptr<std::string>(new std::string(st.c_str()));
    });
    auto res = ss::move_into_vector(range);

    assert(2 == res.size());
    assert("bar" == *res[0]);
    assert("baz" == *res[1]);    
    
}

void test_vector() {
    auto vec = std::vector<std::string>{"foo", "bar", "baz"};
    auto res = ss::move_into_vector(vec);

    assert(3 == res.size());
    assert("foo" == res[0]);
    assert("bar" == res[1]);
    assert("baz" == res[2]);    
}

int main() {
    test_transformed();
    test_filtered();
    test_vector();

    return 0;
}

