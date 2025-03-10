#include "BST.h"

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
        cout << "This value is already in the tree." << endl;
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

bool BinaryTree::contains(Node* node, int value) {
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
        if (node->_left == nullptr && node->_right == nullptr) {
            delete node;
            node = nullptr;
        }
        else if (node->_left == nullptr) {
            Node* tmp = node;
            node = node->_right;
            delete tmp;
        }
        else if (node->_right == nullptr) {
            Node* tmp = node;
            node = node->_left;
            delete tmp;
        }
        else {
            Node* minNode = minNode(node->_right);
            node->_info = minNode->_info;
            erase(node->_right, minNode->_info);
        }
        return true;
    }
}

Node* BinaryTree::minNode(Node* node) {
    if (node->_left == nullptr) {
        return node;
    }
    return minNode(node->_left);
}

void BinaryTree::print() const {
    cout << "Binary Tree: ";
    print(_root);
    cout << endl;
}

bool BinaryTree::insert(int value) {
    return insert(_root, value);
}

bool BinaryTree::contains(int value) {
    return contains(_root, value);
}

bool BinaryTree::erase(int value) {
    return erase(_root, value);
}