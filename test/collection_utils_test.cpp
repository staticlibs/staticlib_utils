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
#include <array>

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
    MyInt(MyInt&&) = delete;
    MyInt& operator=(MyInt&&) = delete;
};



template<typename T, typename E, typename F>
class mapped_iter : public std::iterator<std::input_iterator_tag, E> {
    T delegate;
    F& decorator;
    
public:
    mapped_iter(T delegate, F& decorator) : delegate(std::move(delegate)), decorator(decorator) { }

    mapped_iter& operator++() {
        ++delegate;
        return *this;
    }

    E operator*() {
        return decorator(std::move(*delegate));
    }

    bool operator!=(const mapped_iter& end) {
        return this->delegate != end.delegate;
    }
};


template <typename T, typename F>
class mapped_range {
    T& range;
    F decorator;
        
public:
    typedef decltype(range.begin()) iterator;
    typedef decltype(decorator(std::move(*range.begin()))) value_type;
    
    mapped_range(T& range, F decorator): range(range), decorator(decorator) { }
    
    mapped_iter<iterator, value_type, F> begin() {
        return mapped_iter<iterator, value_type, F>{range.begin(), decorator};
    }
    
    mapped_iter<iterator, value_type, F> end() {
        return mapped_iter<iterator, value_type, F>{range.end(), decorator};
    }
};

template <typename T, typename F>
mapped_range<T, F> transform(T& range, F decorator) {
    return mapped_range<T, F>(range, decorator);
}

template <typename T, typename E, typename F>
class filtered_iter : public std::iterator<std::input_iterator_tag, E> {
    T delegate;
    T delegate_end;
    F& decorator;
    
    E current;

public:
    filtered_iter(T delegate, T delegate_end, F& decorator) : 
    delegate(std::move(delegate)), 
    delegate_end(std::move(delegate_end)), 
    decorator(decorator) { 
        if (this->delegate != this->delegate_end) {
            current = std::move(*delegate);
            if (!this->decorator(current)) {
                next();
            }
        }
    }

    filtered_iter& operator++() {
        next();
        return *this;
    }

    E operator*() {
        return std::move(current);
    }

    bool operator!=(const filtered_iter& end) {
        return this->delegate != end.delegate;
    }
    
private: 
    void next() {
        for (++delegate; delegate != delegate_end; ++delegate) {
            current = std::move(*delegate);
            if (decorator(current)) break;
        }        
    }
};

template <typename T, typename F>
class filtered_range {
    T& range;
    F decorator;
    
public:
    typedef decltype(range.begin()) iterator; 
    typedef typename std::iterator_traits<iterator>::value_type value_type;
    
    filtered_range(T& range, F decorator) : range(range), decorator(decorator) { }

    filtered_iter<iterator, value_type, F> begin() {
        return filtered_iter<iterator, value_type, F>{range.begin(), range.end(), decorator};
    }

    filtered_iter<iterator, value_type, F> end() {
        return filtered_iter<iterator, value_type, F>{range.end(), range.end(), decorator};
    }
};

template <typename T, typename F>
filtered_range<T, F> filter(T& range, F decorator) {
    return filtered_range<T, F>(range, decorator);
}


template<typename T1, typename T2, typename E>
class concatted_iter : public std::iterator<std::input_iterator_tag, E> {
    T1 delegate1;
    T1 delegate1_end;
    T2 delegate2;

public:
    concatted_iter(T1 delegate1, T1 delegate1_end, T2 delegate2) : 
    delegate1(std::move(delegate1)), delegate1_end(std::move(delegate1_end)),
    delegate2(std::move(delegate2)) { }

    concatted_iter& operator++() {
        if (delegate1 != delegate1_end) {
            ++delegate1;
        } else {
            ++delegate2;
        }
        return *this;
    }

    E operator*() {
        if (delegate1 != delegate1_end) {
            return std::move(*delegate1);
        } else {
            return std::move(*delegate2);
        }
    }

    bool operator!=(const concatted_iter& end) {
        return this->delegate1 != end.delegate1 || 
                this->delegate2 != end.delegate2;
    }
};

template <typename T1, typename T2>
class concatted_range {
    T1& range1;
    T2& range2;
    
public:
    typedef decltype(range1.begin()) iterator1;
    typedef decltype(range2.begin()) iterator2;
    typedef typename std::iterator_traits<iterator1>::value_type value_type;
    
    concatted_range(T1& range1, T2& range2) : range1(range1), range2(range2) { }
    
    concatted_iter<iterator1, iterator2, value_type> begin() {
        return concatted_iter<iterator1, iterator2, value_type>{range1.begin(), range1.end(), range2.begin()};
    }

    concatted_iter<iterator1, iterator2, value_type> end() {
        return concatted_iter<iterator1, iterator2, value_type>{range1.end(), range1.end(), range2.end()};
    }
};

template <typename T1, typename T2>
concatted_range<T1, T2> concat(T1& range1, T2& range2) {
    return concatted_range<T1, T2>(range1, range2);
}

std::unique_ptr<MyStr> exlambda(std::unique_ptr<MyInt> st) {
    return std::unique_ptr<MyStr>(new MyStr(std::to_string(st->get_int())));
}

void test_nih() {
    auto vec = std::vector<std::unique_ptr<MyStr>>{};
    vec.emplace_back(new MyStr("40"));
    vec.emplace_back(new MyStr("41"));
    vec.emplace_back(new MyStr("42"));
    vec.emplace_back(new MyStr("43"));
    vec.emplace_back(new MyStr("44"));
    vec.emplace_back(new MyStr("45"));
    vec.emplace_back(new MyStr("46"));
    vec.emplace_back(new MyStr("47"));
    vec.emplace_back(new MyStr("48"));
    
    auto mapped = transform(vec, [](std::unique_ptr<MyStr> st) {
        return std::unique_ptr<MyInt>(new MyInt(std::stoi(st->get_str()) + 100));
    });
    auto mapped2 = transform(mapped, exlambda);
    auto mapped3 = transform(mapped2, [](std::unique_ptr<MyStr> st) {
        return std::unique_ptr<MyInt>(new MyInt(std::stoi(st->get_str()) - 50));
    });
    auto filtered = filter(mapped3, [](std::unique_ptr<MyInt>& st) {
        auto val = st->get_int();
        return val >= 92 && val <= 96 && 94 != val;
    });
    int sum = 0;
    auto mapped4 = transform(filtered, [&sum](std::unique_ptr<MyInt> st) {
        auto val = st->get_int();
        sum += val;
        return std::unique_ptr<MyStr>(new MyStr(std::to_string(val) + "__"));
    });
    
    auto mapped5 = mapped4;
    
    for(auto&& el : mapped5) {
        std::cout << el->get_str() << std::endl;
    }
    
    std::cout << std::endl;
    std::cout << sum << std::endl;
    std::cout << std::endl;
    
    // lambda reuse

    auto vec1 = std::vector<std::unique_ptr<MyInt>>{};
    vec1.emplace_back(new MyInt(40));
    vec1.emplace_back(new MyInt(41));
    vec1.emplace_back(new MyInt(42));

    auto ma1 = transform(vec1, exlambda);
    
    for (auto&& el : ma1) {
        std::cout << el->get_str() << std::endl;
    }
    
    std::cout << std::endl;
    
    // concat 
    auto cvec1 = std::vector<std::unique_ptr<MyInt>>{};
    cvec1.emplace_back(new MyInt(40));
    cvec1.emplace_back(new MyInt(42));
    cvec1.emplace_back(new MyInt(41));

    auto cvec2 = std::vector<std::unique_ptr<MyInt>>{};
    cvec2.emplace_back(new MyInt(42));
    cvec2.emplace_back(new MyInt(43));
    cvec2.emplace_back(new MyInt(44));
    
    auto cvec1_filtered = filter(cvec1, [](std::unique_ptr<MyInt>& st) {
        return 42 != st->get_int();
    });
    
    auto ra1 = transform(cvec1_filtered, exlambda);
    auto ra2 = transform(cvec2, exlambda);
    auto ra2_filtered = filter(ra2, [](std::unique_ptr<MyStr>& st) {
        return "42" != st->get_str();
    });

    auto concatted = concat(ra1, ra2_filtered);
    
    for (auto&& el : concatted) {
        std::cout << el->get_str() << std::endl;
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

