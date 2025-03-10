#include "BST.h"
#include <iostream>

using namespace std;

Node::Node(const int& info) : _info(info), _right(nullptr), _left(nullptr) {}

BinaryTree::BinaryTree() : _root(nullptr) {}

BinaryTree::BinaryTree(const BinaryTree& other) {
    _root = copy(other._root);
}

BinaryTree::~BinaryTree() {
    popNode(_root);
}

BinaryTree& BinaryTree::operator=(const BinaryTree& other) {
    if (this != &other) {
        popNode(_root);
        _root = copy(other._root);
    }
    return *this;
}

bool BinaryTree::insert(Node*& node, int value) {
    if (node == nullptr) {
        node = new Node(value);
        return true;
    }
    if (value == node->_info) {
        return false;
    }
    else if (value < node->_info) {
        return insert(node->_left, value);
    }
    else {
        return insert(node->_right, value);
    }
}

Node* BinaryTree::copy(Node* node) {
    if (node == nullptr) {
        return nullptr;
    }
    Node* newNode = new Node(node->_info);
    newNode->_left = copy(node->_left);
    newNode->_right = copy(node->_right);
    return newNode;
}

void BinaryTree::popNode(Node*& node) {
    if (node != nullptr) {
        popNode(node->_left);
        popNode(node->_right);
        delete node;
        node = nullptr;
    }
}

void BinaryTree::print(Node* node) const {
    if (node != nullptr) {
        print(node->_left);
        cout << node->_info << " ";
        print(node->_right);
    }
}

bool BinaryTree::contains(Node* node, int value) const {
    if (node == nullptr) {
        return false;
    }
    if (value == node->_info) {
        return true;
    }
    else if (value < node->_info) {
        return contains(node->_left, value);
    }
    else {
        return contains(node->_right, value);
    }
}

bool BinaryTree::erase(Node*& node, int value) {
    if (node == nullptr) {
        return false;
    }
    if (value < node->_info) {
        return erase(node->_left, value);
    }
    else if (value > node->_info) {
        return erase(node->_right, value);
    }
    else {
        if (node->_left == nullptr) {
            Node* temp = node->_right;
            delete node;
            node = temp;
        }
        else if (node->_right == nullptr) {
            Node* temp = node->_left;
            delete node;
            node = temp;
        }
        else {
            Node* minNode = node->_right;
            while (minNode->_left != nullptr) {
                minNode = minNode->_left;
            }
            node->_info = minNode->_info;
            erase(node->_right, minNode->_info);
        }
        return true;
    }
}

bool BinaryTree::operator!=(const BinaryTree& other) const {
    return !(*this == other);
}

bool BinaryTree::operator==(const BinaryTree& other) const {
    return compareTrees(_root, other._root);
}

bool BinaryTree::compareTrees(Node* node1, Node* node2) const {
    if (node1 == nullptr && node2 == nullptr) return true;
    if (node1 == nullptr || node2 == nullptr) return false;
    return (node1->_info == node2->_info) &&
        compareTrees(node1->_left, node2->_left) &&
        compareTrees(node1->_right, node2->_right);
}

bool BinaryTree::insert(int value) {
    return insert(_root, value);
}

bool BinaryTree::contains(int value) const {
    return contains(_root, value);
}

bool BinaryTree::erase(int value) {
    return erase(_root, value);
}

void BinaryTree::print() const {
    cout << "Binary Tree: ";
    print(_root);
    cout << endl;
}