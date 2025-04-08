#pragma once

template <typename K, typename V>
class Pair {
public:
    K key; 
    V value; 

    Pair(const K& k, const V& v) : key(k), value(v) {}

    bool operator==(const Pair& other) const {
        return key == other.key && value == other.value;
    }
};