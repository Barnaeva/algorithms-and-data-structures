#include <iostream>
#include "BinaryTree.h"
#include "TimeTest.h"
#include "Duplicates.h"

using namespace std;

int main() {
    try {
        BinaryTree tree;

        tree.insert(10);
        tree.insert(5);
        tree.insert(15);
        tree.insert(3);
        tree.insert(7);
        tree.insert(12);
        tree.insert(18);

        tree.print();

        cout << "Contains 10: " << (tree.contains(10) ? "Yes" : "No") << endl;
        cout << "Contains 6: " << (tree.contains(6) ? "Yes" : "No") << endl;

        cout << "Removing element 10" << endl;
        tree.erase(10);
        tree.print();

        cout << "Removing element 5" << endl;
        tree.erase(5);
        tree.print();

        BinaryTree copiedTree = tree;
        cout << "Copied tree:" << endl;
        copiedTree.print();

        /*vector<size_t> sizes = {1000, 10000, 100000};

        for (size_t size : sizes) {
            measureFillTimeTree(size);
            measureFillTimeVector(size);
            measureSearchTimeTree(size);
            measureSearchTimeVector(size);
            measureAddRemoveTimeTree(size);
            measureAddRemoveTimeVector(size);
        }

        */

        vector<int> vec = { 3, 2, 2, 4, 2, 5, 6, 4, 3, 70, 5, 33, 55, 8, 6, 9};
        vector<int> duplicates = findDuplicates(vec);

        cout << "Duplicates: ";
        for (const auto& num : duplicates) {
            cout << num << " ";
        }
        cout << endl;
    }
    catch (const exception& e) {
        cerr << "An error occurred: " << e.what() << endl;
    }
    return 0;
}