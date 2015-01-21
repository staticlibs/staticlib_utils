/* 
 * File:   linked_hash_map_test.cpp
 * Author: alex
 *
 * Created on January 21, 2015, 2:28 PM
 */

#include <iostream>
#include <string>
#include <functional>

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
    std::string f1;
    std::string f2;
    size_t hash;
    
public:
    class Hasher {
        public: size_t operator()(const MyNode& node) const {
            (void) node;
            return 1;
            //        return node.hash;
        }
    };
    
    class Equalizer {
        public: bool operator()(const MyNode& lhs, const MyNode& rhs) const {
            (void) lhs;
            (void) rhs;
            return true;
        }
    };

    // business part
    
    MyNode(std::string key, std::string f1, std::string f2) :
    key(key), f1(f1), f2(f2), hash(string_hasher(key)) { }    
    
    std::string print() {
        return f1 + ":" + f2;
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
        
    map.emplace("foo", "41", "42");
    map.emplace("bar", "43", "44");
    
    for(auto a : map) {
        std::cout << a.print() << std::endl;
    }
    
    return 0;
}

