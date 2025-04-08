#include <iostream>
#include <cstdlib>
#include <ctime>
#include <list>
#include <string>
#include <vector>
#include <numeric>
#include <array>
#include <random>
#include "Pair.h"

using namespace std;

#pragma once

template <typename K, typename V, template <typename...> class Container = std::list>
class HashTable {
private:
    Container<Pair<K, V>>* table;
    size_t capacity;

    size_t hash_function(const K& key) const;

public:
    HashTable(size_t cap, bool random = false);
    HashTable(const HashTable& other);
    HashTable& operator=(const HashTable& other);
    ~HashTable();

    bool insert(const K& key, const V& value);
    void insert_or_assign(const K& key, const V& value);
    bool contains(const V& value) const;
    Pair<K, V>* search(const K& key);
    bool erase(const K& key);
    int count(const K& key) const;
    void print() const;
};
template <typename K, typename V, template <typename...> class Container>
HashTable<K, V, Container>::HashTable(size_t cap, bool random) : capacity(cap) {
    table = new Container<Pair<K, V>>[capacity];

    if (random) {
        vector<unsigned char> values(256);
        iota(values.begin(), values.end(), 0);
        shuffle(values.begin(), values.end(), mt19937(random_device{}()));

        for (int i = 0; i < 256; ++i) {
            insert(static_cast<unsigned char>(i), values[i]);
        }
    }
}

template <typename K, typename V, template <typename...> class Container>
HashTable<K, V, Container>::HashTable(const HashTable& other)
    : capacity(other.capacity) {
    table = new Container<Pair<K, V>>[capacity];
    for (size_t i = 0; i < capacity; ++i) {
        table[i] = other.table[i];
    }
}

template <typename K, typename V, template <typename...> class Container>
HashTable<K, V, Container>& HashTable<K, V, Container>::operator=(const HashTable& other) {
    if (this != &other) {
        delete[] table;
        capacity = other.capacity;
        table = new Container<Pair<K, V>>[capacity];
        for (size_t i = 0; i < capacity; ++i) {
            table[i] = other.table[i];
        }
    }
    return *this;
}

template <typename K, typename V, template <typename...> class Container>
HashTable<K, V, Container>::~HashTable() {
    delete[] table;
}

template <typename K, typename V, template <typename...> class Container>
size_t HashTable<K, V, Container>::hash_function(const K& key) const {
    return static_cast<size_t>(key) % capacity;
}

template <typename K, typename V, template <typename...> class Container>
bool HashTable<K, V, Container>::insert(const K& key, const V& value) {
    size_t index = hash_function(key);
    for (auto& pair : table[index]) {
        if (pair.key == key) {
            return false;
        }
    }
    table[index].emplace_back(key, value);
    return true;
}

template <typename K, typename V, template <typename...> class Container>
void HashTable<K, V, Container>::insert_or_assign(const K& key, const V& value) {
    size_t index = hash_function(key);
    for (auto& pair : table[index]) {
        if (pair.key == key) {
            pair.value = value;
            return;
        }
    }
    table[index].emplace_back(key, value);
}

template <typename K, typename V, template <typename...> class Container>
bool HashTable<K, V, Container>::contains(const V& value) const {
    for (size_t i = 0; i < capacity; ++i) {
        for (const auto& pair : table[i]) {
            if (pair.value == value) {
                return true;
            }
        }
    }
    return false;
}

template <typename K, typename V, template <typename...> class Container>
Pair<K, V>* HashTable<K, V, Container>::search(const K& key) {
    size_t index = hash_function(key);
    for (auto& pair : table[index]) {
        if (pair.key == key) {
            return &pair;
        }
    }
    return nullptr;
}

template <typename K, typename V, template <typename...> class Container>
bool HashTable<K, V, Container>::erase(const K& key) {
    size_t index = hash_function(key);
    auto& chain = table[index];
    for (auto it = chain.begin(); it != chain.end(); ++it) {
        if (it->key == key) {
            chain.erase(it);
            return true;
        }
    }
    return false;
}

template <typename K, typename V, template <typename...> class Container>
int HashTable<K, V, Container>::count(const K& key) const {
    size_t index = hash_function(key);
    return static_cast<int>(table[index].size());
}

template <typename K, typename V, template <typename...> class Container>
void HashTable<K, V, Container>::print() const {
    for (size_t i = 0; i < capacity; ++i) {
        std::cout << "Bucket " << i << ": ";
        for (const auto& pair : table[i]) {
            std::cout << "[" << pair.key << ": " << pair.value << "] ";
        }
        std::cout << std::endl;
    }
}