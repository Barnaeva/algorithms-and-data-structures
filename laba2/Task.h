#include "HashTable.h"

#pragma once

using namespace std;

size_t pearson_hash(const std::string& input, HashTable<size_t, size_t>& table) {
    size_t hash = 0;
    for (char c : input) {
        size_t index = (hash ^ static_cast<size_t>(c));
        Pair<size_t, size_t>* pair = table.search(index);
        if (pair) {
            hash = pair->value;
        }
    }
    return hash;
}

bool compare_hashes(size_t saved_hash, const std::string& input_string, HashTable<size_t, size_t>& table) {
    size_t new_hash = pearson_hash(input_string, table);
    return saved_hash == new_hash;
}