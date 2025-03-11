#include "BinaryTree.h"
#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

void printVector(const vector<int>& vec) {
    for (const auto& num : vec) {
        cout << num << " ";
    }
    cout << endl;
}

vector<int> findUnique(const vector<int>& vec) {
    BinaryTree tree;
    vector<int> duplicates;

    for (int x : vec) {
        if (!tree.insert(x)) duplicates.push_back(x);
    }

    for (int x : duplicates) {
        if (tree.contains(x)) {
            tree.erase(x);
        }
    }

    vector<int> unique;

    tree.inOrderTraversal(unique);

    return unique;
}

