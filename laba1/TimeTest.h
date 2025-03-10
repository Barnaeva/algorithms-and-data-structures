#include "BinaryTree.h"
#include <vector>
#include <chrono>
#include <random>
#include <iostream>

using namespace std;

size_t lcg() {
    static size_t x = 0;
    x = (1021 * x + 24631) % 116640;
    return x;
}

void fillContainer(BinaryTree& tree, int size) {
    for (int i = 0; i < size; ++i) {
        int key = lcg() % size * 2;
        while (!tree.insert(key)) {
            key = lcg() % size * 2;
        }
    }
}

void fillVector(vector<int>& vec, int size) {
    for (int i = 0; i < size; ++i) {
        int key = lcg() % size * 2;
        while (find(vec.begin(), vec.end(), key) != vec.end()) {
            key = lcg() % size * 2;
        }
        vec.push_back(key);
    }
}

void measureFillTimeTree(int size) {
    BinaryTree tree;
    auto start = chrono::high_resolution_clock::now();
    fillContainer(tree, size);
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
    cout << "Average fill time for BinaryTree (" << size << "): " << duration << " microseconds" << endl;
}

void measureFillTimeVector(int size) {
    vector<int> vec;
    auto start = chrono::high_resolution_clock::now();
    fillVector(vec, size);
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
    cout << "Average fill time for std::vector<int> (" << size << "): " << duration << " microseconds" << endl;
}

void measureSearchTimeTree(int size) {
    BinaryTree tree;
    fillContainer(tree, size);
    int key = lcg() % size * 2;
    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i) {
        tree.contains(key);
    }
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
    cout << "Average search time in BinaryTree (" << size << "): " << duration / 1000.0 << " microseconds" << endl;
}

void measureSearchTimeVector(int size) {
    vector<int> vec;
    fillVector(vec, size);
    int key = lcg() % size * 2;
    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i) {
        find(vec.begin(), vec.end(), key) != vec.end();
    }
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
    cout << "Average search time in std::vector<int> (" << size << "): " << duration / 1000.0 << " microseconds" << endl;
}

void measureAddRemoveTimeTree(int size) {
    BinaryTree tree;
    fillContainer(tree, size);
    int key = lcg() % size * 2;
    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i) {
        tree.insert(key);
        tree.erase(key);
    }
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
    cout << "Average add and remove time in BinaryTree (" << size << "): " << duration / 2000.0 << " microseconds" << endl;
}

void measureAddRemoveTimeVector(int size) {
    vector<int> vec;
    fillVector(vec, size);
    int key = lcg() % size * 2;
    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i) {
        vec.push_back(key);
        vec.pop_back();
    }
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
    cout << "Average add and remove time in std::vector<int> (" << size << "): " << duration / 2000.0 << " microseconds" << endl;
}
