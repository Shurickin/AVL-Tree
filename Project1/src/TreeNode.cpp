#include "TreeNode.h"

BST::TreeNode::TreeNode(string name, int id) {
	inOrderNum = 0;
	ID = id;
	NAME = name;
	height = 0; // can make height of node function with the left and right children *****( 1-based height)****
	left = nullptr;
	right = nullptr;
}

BST::TreeNode::~TreeNode() {
	//delete this->left;
	//delete this->right;
}

int BST::getBalance(TreeNode* head) {
	if (head == nullptr) {
		return 0;
	}
	return heights(head->left) - heights(head->right);
}

BST::TreeNode* BST::leftRoto(TreeNode* head) {
	TreeNode* temp = head;
	temp = head->right;
	head->right = temp->left;
	temp->left = head;

	head->height = heights(head);
	temp->height = heights(temp);
	return temp;
}

BST::TreeNode* BST::rightRoto(TreeNode* head) {
	TreeNode* temp = head;
	temp = head->left;
	head->left = temp->right;
	temp->right = head;

	head->height = heights(head);
	temp->height = heights(temp);
	return temp;
}

BST::TreeNode* BST::helperInsert(TreeNode* root, string name, int id) {
	int check = 0;
	const char* Name = name.c_str();
	for (int i = 1; i<name.length() - 1; i++) {
		check = isalpha(Name[i]);
		if (check == 0) { // if not in alphabet
			cout << "Unsuccessful\n";
			return NULL;
		}
	}
	if (id >= 100000000) { // if greater than or equal to 9 digits
		cout << "Unsuccessful\n";
		return NULL;
	}

	if (root == nullptr) {
		cout << "Successful\n";
		numOfNodes++;
		return new TreeNode(name, id);
	}
	else if (id > root->ID) {
		root->right = helperInsert(root->right, name, id);
	}
	else {
		root->left = helperInsert(root->left, name, id);
	}
	
	root->height = heights(root);

	if (getBalance(root) >= 2) {// if tree is left heavy
		if (id < root->left->ID) {// if left subtree is right heavy
			return rightRoto(root);
		}
		else {
			root->left = leftRoto(root->left);
			return rightRoto(root);
		}
	}
	else if (getBalance(root) <= -2) {
		if (id < root->right->ID) {
			root->right = rightRoto(root->right);
			return leftRoto(root);
		}
		else {
			return leftRoto(root);
		}
	}
	return root;
}

int BST::heights(TreeNode* head) {
	if (head == nullptr) {
		return 0;
	}
	auto leftHeight = heights(head->left);
	auto rightHeight = heights(head->right);
	if (leftHeight > rightHeight) {
		return leftHeight + 1;
	}
	else {
		return rightHeight + 1;
	}
}

void BST::searchName(TreeNode* head, string name, bool &isHere) {
	if (head == nullptr) {

	}
	else {
		if (head->NAME == name) {
			printID(head);
			cout << head->ID << "\n";
			isHere = true;
		}
		searchName(head->left, name, isHere);
		searchName(head->right, name, isHere);
	}
}

void BST::searchID(TreeNode* head, int id, bool &isHere) {
	if (head == nullptr) {

	}
	else {
		searchID(head->left, id, isHere);
		if (head->ID == id) {
			cout << head->NAME.substr(1, head->NAME.length() - 2) << "\n";
			isHere = true;
		}
		searchID(head->right, id, isHere);
	}
}

void BST::printPostOrder(TreeNode* head, bool& first) {
	if (head == nullptr) {
		cout << "";
	}
	else {
		printPostOrder(head->left,first);
		printPostOrder(head->right,first);
		if (first == true) {
			first = false;
		}
		else{
			cout << ", ";
		}
		cout << head->NAME.substr(1, head->NAME.length() - 2);
	}
}

void BST::printPreOrder(TreeNode* head, bool& first) {
	if (head == nullptr) {
		cout << "";
	}
	else {
		if (first == true) {
			first = false;
		}
		else {
			cout << ", ";
		}
		cout << head->NAME.substr(1, head->NAME.length() - 2);
		printPreOrder(head->left,first);
		printPreOrder(head->right,first);
	}
}

void BST::printInOrder(TreeNode* head, bool& first) {
	if (head == nullptr) {
		cout << "";
	}
	else {
		printInOrder(head->left, first);
		if (first == true) {
			first = false;
		}
		else {
			cout << ", ";
		}
		cout << head->NAME.substr(1, head->NAME.length() - 2);
		printInOrder(head->right, first);
	}
}

void BST::printLevelCount(TreeNode* root) {
	queue<TreeNode*> q;
	int levelCount = 0;

	if (root == nullptr) {
		cout << "0";
		return;
	}

	q.push(root);
	q.push(nullptr);
	levelCount++;

	while (!q.empty()) {
		TreeNode* curr = q.front();
		q.pop();

		if (curr != nullptr) {

			if (curr->left != nullptr) {
				q.push(curr->left);
			}
			if (curr->right != nullptr) {
				q.push(curr->right);
			}
		}
		else if (!q.empty()) {
			q.push(nullptr); // denotes end of every level
			levelCount++;
		}
	}

	cout << levelCount;
}

void BST::printID(TreeNode* node) {
	if (node->ID < 10)
		cout << "0000000";
	else if (node->ID < 100)
		cout << "000000";
	else if (node->ID < 1000)
		cout << "00000";
	else if (node->ID < 10000)
		cout << "0000";
	else if (node->ID < 100000)
		cout << "000";
	else if (node->ID < 1000000)
		cout << "00";
	else if (node->ID < 10000000)
		cout << "0";
}

BST::TreeNode* BST::findParent(TreeNode* &curr, TreeNode*& parent, int id) {
	while (curr != nullptr && curr->ID != id) { //stops on node
		parent = curr; // update parent to curr

		if (id < curr->ID) {
			curr = curr->left;
		}
		else {
			curr = curr->right;
		}
	}
	return parent;
}

BST::TreeNode* BST::removeInorder(TreeNode* head, int number, int &count, bool &isHere){
	if (head == nullptr) {
		return head;
	}
	else {
		if (count <= number) {
			head->left = removeInorder(head->left, number, count, isHere);
			count++;
			if (count == number) { // have if statement for if parent is null
				isHere = true;
				TreeNode* parent = nullptr;
				parent = findParent(root, parent, head->ID);
				if (parent == nullptr) {
					return removeID(root, root->ID, isHere);
				}
				else{
					return removeID(head, head->ID, isHere);
				}
			}
			head->right = removeInorder(head->right, number, count, isHere);
		}
	}
	return head;
}

BST::TreeNode* BST::removeID(TreeNode* head, int id, bool &isHere) {
	if (head == nullptr) {
		return head;
	}
	
	if (id < head->ID) {
		head->left = removeID(head->left, id, isHere);
	}
	else if (id > head->ID) {
		head->right = removeID(head->right, id, isHere);
	}
	else { // it is the head
		isHere = true;
		if (head->left == nullptr && head->right == nullptr) {
			delete head;
			numOfNodes--;
			head = nullptr;
			return nullptr;
		}
		else if (head->left == nullptr) {
			TreeNode* temp = head->right;
			delete head;
			numOfNodes--;
			return temp;
		}
		else if (head->right == nullptr) {
			TreeNode* temp = head->left;
			delete head;
			numOfNodes--;
			return temp;
		}
		else {
			TreeNode* successor = inorderSuccessor(head->right);
			head->NAME = successor->NAME;
			head->ID = successor->ID;

			head->right = removeID(head->right, successor->ID, isHere);
		}
		return head;
	}
}

BST::TreeNode* BST::inorderSuccessor(TreeNode* head) { // use head of the right subtree
	TreeNode* curr = head;

	/* loop down to find the leftmost leaf */
	while (curr && curr->left != nullptr)
		curr = curr->left;

	return curr;
}