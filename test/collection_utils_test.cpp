/* 
 * File:   collection_utils_test.cpp
 * Author: alex
 *
 * Created on January 25, 2015, 11:03 PM
 */

#include <cassert>
#include <vector>
#include <utility>
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

//#include <chain.hpp>
//#include <filter.hpp>
//#include <imap.hpp>

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
////
////    auto vec2 = std::vector<std::unique_ptr <std::string>>{};
////    vec2.emplace_back(new std::string("43"));
////    vec2.emplace_back(new std::string("44"));
////    (void) vec2;
//
////    auto joined_vectors = range::join(vec1, vec2);
////    auto joined_vectors = iter::chain(vec1, vec2);
////    for (auto&& el : joined_vectors) {
////        std::cout << *el << std::endl;
////    }
//    
////    auto vecwr = std::vector<int>{51, 52, 53};
//     
//    auto wrapped1  = adaptors::transform(vec1, [](std::unique_ptr<std::string>& st) {
//        return &st;
//    });
//    
//    auto range1 = adaptors::transform(wrapped1, [](const std::unique_ptr<std::string>* st) {
//        st->get()->append("_1");
//        return st;
//    }); 
//
//    auto range12 = adaptors::transform(range1, [](const std::unique_ptr<std::string>* st) {
//        st->get()->append("_2");
//        return st;
//    }); 
//    
//    auto range12_filtered = adaptors::filter(range12, [](const std::unique_ptr<std::string>* st) {
//        return "40_1_2" != *(st->get());
//    });
//
//    for (auto el : range12_filtered) {
//        std::cout << *el->get() << std::endl;
//    }

//    auto range2 = iter::imap([](const std::unique_ptr<std::string>& st) {
//        auto res = std::move(st);
//        res->append("_2");
//        return res;
//    }, vec2);
//
//    auto vec3 = std::vector<std::unique_ptr<std::string>>{};
//    vec2.emplace_back(new std::string("45"));
//    vec2.emplace_back(new std::string("46"));
//    
//    auto range3 = iter::imap([](std::unique_ptr<std::string>& st) {
//        return std::move(st);
//    }, vec3);
//    
//    auto joined_vectors = iter::chain(range2, range12, range3);
//    auto vec = ss::emplace_to_vector(joined_vectors);
////    for (auto&& el : joined_vectors) {
////        std::cout << *el << std::endl;
////    }
//    
//    std::cout << vec.size() << std::endl;
//    std::cout << *vec[0] << std::endl;
//    std::cout << *vec[vec.size()-1] << std::endl;
    


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

class MyStr {
    std::string val;
    
public:    
    MyStr(std::string val) : val(val) { }
    
    std::string get_str() {
        return val;
    }
    
    MyStr(const MyStr&) = delete;
    MyStr& operator=(const MyStr&) = delete;
    MyStr(MyStr&&) = delete;
    MyStr& operator=(MyStr&&) = delete;
};

class MyInt {
    int val;

public:

    MyInt(int val) : val(val) { }

    int get_int() {
        return val;
    }

    MyInt(const MyInt&) = delete;
    MyInt& operator=(const MyInt&) = delete;
    MyInt(MyStr&&) = delete;
    MyInt& operator=(MyInt&&) = delete;
};



template<typename T, typename E, typename F>
class mapped_iter : public std::iterator<std::input_iterator_tag, E> {
    T delegate;
    F& decorator;
    
public:
    typedef E value_type;

    mapped_iter(T delegate, F& decorator) : delegate(std::move(delegate)), decorator(decorator) { }


    mapped_iter& operator++() {
        ++delegate;
        return *this;
    }

    value_type operator*() const {
        return decorator(std::move(*delegate));
    }

    bool operator!=(const mapped_iter& end) {
        return this->delegate != end.delegate;
    }
};


template <typename T, typename E, typename F>
class mapped_range {
private:
    T& range;
    F decorator;
        
public:
    typedef decltype(range.begin()) iter_type;
    typedef E value_type;
    
    mapped_range(T& range, F decorator): range(range), decorator(std::move(decorator)) { }
    
    mapped_iter<iter_type, value_type, F> begin() {
        return mapped_iter<iter_type, value_type, F>{range.begin(), decorator};
    }
    
    mapped_iter<iter_type, value_type, F> end() {
        return mapped_iter<iter_type, value_type, F>{range.end(), decorator};
    }
};


template <typename E, typename T, typename F>
mapped_range<T, E, F> make_mapped_range(T& range, F decorator) {
    return mapped_range<T, E, F>(range, std::move(decorator));
}

void test_nih() {
    auto vec = std::vector<std::unique_ptr<MyStr>>{};
    vec.emplace_back(new MyStr("40"));
    vec.emplace_back(new MyStr("41"));
    vec.emplace_back(new MyStr("42"));
    
    auto mapped = make_mapped_range<std::unique_ptr<MyInt>>(vec, [](std::unique_ptr<MyStr> st) {
        return std::unique_ptr<MyInt>(new MyInt(std::stoi(st->get_str()) + 100));
    });
    auto mapped2 = make_mapped_range<std::unique_ptr<MyStr>>(mapped, [](std::unique_ptr<MyInt> st) {
        return std::unique_ptr<MyStr>(new MyStr(std::to_string(st->get_int())));
    });
    auto mapped3 = make_mapped_range<std::unique_ptr<MyInt>>(mapped2, [](std::unique_ptr<MyStr> st) {
        return std::unique_ptr<MyInt>(new MyInt(std::stoi(st->get_str()) - 50));
    });
    
    
//    auto it = mapped2.begin();
//    ++it;
//    (void) it;
    for(auto&& el : mapped3) {
        std::cout << el->get_int() << std::endl;
    }
}

int main() {
    test_transformed();
    test_filtered();
    test_vector();
    test_emplate_to();
    test_join();
    test_nih();

    return 0;
}

