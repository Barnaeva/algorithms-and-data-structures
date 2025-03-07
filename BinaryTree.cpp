struct Node {
	int _info;
	Node* _right, * _left;
	Node(const int& info) :_info(info), _right(nullptr), _left(nullptr) {}
};

class BinaryTree {
private:
	Node* _root;
	void insert(Node*& node, int value) {
		if (node == nullptr) {
			node = new Node(value);
		}
		else if (value < node->_info) {
			insert(node->_left, value);
		}
		else if (value > node->_info) {
			insert(node->_right, value);
		}
	}
	Node* copy(Node*& node) {
		if (node == nullptr) {
			return nullptr;
		}
		Node* newNode = new Node(node->_info);
		newNode->_left = copy(node->_left);
		newNode->_right = copy(node->_right);
	}
	void popNode(Node*& node) {
		if (node == nullptr) {
			popNode(node->_left);
			popNode(node->_left);
			delete node;
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


};