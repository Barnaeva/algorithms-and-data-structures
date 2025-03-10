#include <vector>
#pragma once

struct Node {
    int _info;
    Node* _right;
    Node* _left;
    Node(const int& info);
};

class BinaryTree {
private:
    Node* _root;

    bool insert(Node*& node, int value);
    Node* copy(Node* node);
    void popNode(Node*& node);
    void print(Node* node) const;
    bool contains(Node* node, int value) const;
    bool erase(Node*& node, int value);
    bool compareTrees(Node* node1, Node* node2) const;
    void inOrderTraversal(Node* node, std::vector<int>& result) const;

public:
    BinaryTree();
    BinaryTree(const BinaryTree& other);
    ~BinaryTree();
    BinaryTree& operator=(const BinaryTree& other);
    void print() const;
    bool insert(int value);
    bool contains(int value) const;
    bool erase(int value);
    bool operator!=(const BinaryTree& other) const;
    bool operator==(const BinaryTree& other) const;
    void clear();
    void inOrderTraversal(std::vector<int>& result) const;
};