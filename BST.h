#ifndef BST_H
#define BST_H

#include <iostream>
using namespace std;

struct Node {
    int _info;
    Node* _right;
    Node* _left;

    Node(const int& info) : _info(info), _right(nullptr), _left(nullptr) {}
};

class BinaryTree {
private:
    Node* _root;

    bool insert(Node*& node, int value);
    Node* copy(Node* node);
    void popNode(Node*& node);
    void print(Node* node) const;
    bool contains(Node* node, int value);
    bool erase(Node*& node, int value);
    Node* minNode(Node* node);

public:
    BinaryTree();
    BinaryTree(const BinaryTree& other);
    ~BinaryTree();
    BinaryTree& operator=(const BinaryTree& other);

    void print() const;
    bool insert(int value);
    bool contains(int value);
    bool erase(int value);
};

#endif