#include "BinaryTree.h"
#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

void extractDuplicates(Node* node, vector<int>& duplicates) {
    if (node != nullptr) {
        extractDuplicates(node->_left, duplicates);
        duplicates.push_back(node->_info);
        extractDuplicates(node->_right, duplicates);
    }
}

vector<int> findDuplicates(const vector<int>& vec) {
    unordered_map<int, int> countMap;
    BinaryTree tree;

    for (const auto& num : vec) {
        if (countMap.find(num) != countMap.end()) {
            countMap[num]++;
        }
        else {
            countMap[num] = 1;
        }
    }

    for (const auto& pair : countMap) {
        if (pair.second > 1) {
            tree.insert(pair.first);
        }
    }

    vector<int> duplicates;
    tree.inOrderTraversal(duplicates);

    return duplicates;
}

