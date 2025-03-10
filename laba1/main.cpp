#include <iostream>
#include "BST.h"

using namespace std;
int main() {
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

    return 0;
}