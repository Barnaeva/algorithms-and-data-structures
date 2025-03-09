#include <iostream>
using namespace std;
struct Node {
	int _info;
	Node* _right, * _left;
	Node(const int& info) :_info(info), _right(nullptr), _left(nullptr) {}
};

class BinaryTree {
private:
	Node* _root;

	bool insert(Node*& node, int value) {
		if (value==node->_info) {
			cout << "this value is already in the tree." << endl;
			return false;
		}
		else if (node == nullptr) {
			node = new Node(value);
			return true;
		}
		else if (value < node->_info) {
			return insert(node->_left, value);
		}
		else if (value > node->_info) {
			return insert(node->_right, value);
		}
	}

	Node* copy(Node*& node) {
		if (node == nullptr) {
			return nullptr;
		}
		Node* newNode = new Node(node->_info);
		newNode->_left = copy(node->_left);
		newNode->_right = copy(node->_right);
		return newNode;
	}
	void popNode(Node*& node) {
		if (node == nullptr) {
			popNode(node->_left);
			popNode(node->_left);
			delete node;
		}
	}
	void print(Node* node) const {
		if (node != nullptr) {
			print(node->_left);
			cout << node->_info<<" ";			
			print(node->_right);
		}
	}
	bool contains(Node* node, int value) {
		if (node == nullptr) {
			return false;
		}
		else if (value == node->_info) {
			return true;
		}
		else if (value < node->_info) {
			return contains(node->_left,value);
		}
		else if (value > node->_info) {
			return contains(node->_right,value);
		}
	}
	bool erase(Node*& node, int value) {
		if (node == nullptr) {
			return false;
		}
		else if (value == node->_info) {
			if (node->_left == nullptr && node->_right == nullptr) {
				delete node;
				node = nullptr;
				return true;
			}
			else if (node->_left != nullptr && node->_right == nullptr) {
				Node* tmp = node;
				node = node->_left;
				delete tmp;
				return true;
			}
			else if (node->_right != nullptr && node->_left == nullptr) {
				Node* tmp = node;
				node = node->_right;
				delete tmp;
				return true;
			}
			else {
				Node* tmp = minNode(node->_right);
				node->_info = tmp->_info;
				return erase(node->_right, tmp->_info);
			}
		}
		else if (value < node->_info) {
			return erase(node->_left, value);
		}
		else {
			return erase(node->_right, value);
		}
	}

	Node* minNode(Node* node) {
		if (node->_left == nullptr) {
			return node;
		}
		else {
			return minNode(node->_left);
		}
	}

public:
	BinaryTree() :_root(nullptr) {}

	BinaryTree(const BinaryTree& other) {
		copy(other._root);
		popNode(other._root);
	}

	~BinaryTree() {
		popNode(_root);
	}

	BinaryTree operator=(const BinaryTree& other) {
		if (this != other) {
			popNode(_root);
			_root = copy(other._root);
		}
		return *this;
	}

	void print() const {
		cout << "Binary Tree:";
		print(_root);
		cout << endl;
	}

	bool insert(int value) {
		return insert(_root, value);
	}
	bool contains(int value) {
		return contains(_root, value);
	}
	bool erase(int value) {
		return erase(_root, value);
	}
};