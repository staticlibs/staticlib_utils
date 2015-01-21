/* 
 * File:   linked_hash_map_test.cpp
 * Author: alex
 *
 * Created on January 21, 2015, 2:28 PM
 */

#include <iostream>
#include <string>
#include <functional>
#include <cassert>

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <boost/multi_index/identity.hpp>

namespace {
    std::hash<std::string> string_hasher{};
}

namespace my {

class MyNode {
    std::string key;
    uint32_t f1;
    size_t hash;
    
public:
    class Hasher {
        public: size_t operator()(const MyNode& node) const {
            return node.hash;
        }
    };
    
    class Equalizer {
        public: bool operator()(const MyNode& lhs, const MyNode& rhs) const {
            return lhs.key == rhs.key;
        }
    };

    // business part
    
    MyNode(std::string key, uint32_t f1) :
    key(key), f1(f1), hash(string_hasher(key)) { }    
    
    uint32_t get_val() {
        return f1;
    }
};

}


int main() {
 
    boost::multi_index_container<
        my::MyNode,
        boost::multi_index::indexed_by<
            boost::multi_index::hashed_unique<
                boost::multi_index::identity<my::MyNode>,
                my::MyNode::Hasher,
                my::MyNode::Equalizer>,
            boost::multi_index::sequenced<>>>
    map{};
    
    for (auto i = 0; i < 1000; i++) {
        auto st = std::to_string(i);
        map.emplace(st, i);
    }
    
    uint32_t val = 0;
    for(auto a : map.get<1>()) {
        assert(val == a.get_val());
        val += 1;
    }
    
    return 0;
}

