#include "BST.h"

int main() {
    BinaryTree tree;

    cout << "Inserting elements into the tree:" << endl;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(2);
    tree.insert(4);
    tree.insert(6);
    tree.insert(8);

    tree.print();

    cout << "Checking if certain elements are in the tree:" << endl;
    cout << "Contains 4: " << (tree.contains(4) ? "Yes" : "No") << endl;
    cout << "Contains 10: " << (tree.contains(10) ? "Yes" : "No") << endl;

    cout << "Removing elements from the tree:" << endl;
    tree.erase(3);
    cout << "After removing 3:" << endl;
    tree.print();

    tree.erase(5);
    cout << "After removing 5:" << endl;
    tree.print();

    tree.erase(10);
    cout << "After trying to remove 10 (not in tree):" << endl;
    tree.print();

    return 0;
}