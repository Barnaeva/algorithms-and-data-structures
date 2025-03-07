struct Node {
	int _info;
	Node *_right,*_left;
	Node(const int& info) :_info(info),_right(nullptr),_left(nullptr){}
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
public:
	BinaryTree():_root(nullptr) {}
	BinaryTree(const BinaryTree& other) {

	}

	

};