#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <cctype>
using namespace std;

class BST {
	private:
		struct TreeNode
		{
			int ID, height, inOrderNum;
			string NAME;
			TreeNode* left;
			TreeNode* right;

			TreeNode(string name, int id);
			~TreeNode();
		};

		int numOfNodes = 0;
		TreeNode* root = nullptr;
		TreeNode* helperInsert(TreeNode* root, string name, int id); // done
		int heights(TreeNode* root);
		int getBalance(TreeNode* head);

		// can use queue to find the number of levels
		TreeNode* leftRoto(TreeNode* head);
		//void leftRightRoto(TreeNode* head);
		TreeNode* rightRoto(TreeNode* head);
		TreeNode* findParent(TreeNode* &curr, TreeNode* &parent, int id);
		void searchName(TreeNode* head, string name, bool &isHere);
		void searchID(TreeNode* head, int id, bool &isHere); // find a way to know that an ID wasnt found
		void printPostOrder(TreeNode* head, bool& first); // done
		void printPreOrder(TreeNode* head, bool& first); // done
		void printInOrder(TreeNode* head, bool& first); // done
		void printLevelCount(TreeNode* root);
		void printID(TreeNode* node);
		TreeNode* removeInorder(TreeNode* head, int number, int &count, bool &isHere);
		TreeNode* removeID(TreeNode* head, int id, bool &isHere);
		TreeNode* inorderSuccessor(TreeNode* head);
		
public:
	void printInOrder() {
		bool first = true;
		BST::printInOrder(root,first);
		cout << "\n";
	}
	void printPreOrder() {
		bool first = true;
		BST::printPreOrder(root, first);
		cout << "\n";
	}
	void printPostOrder() {
		bool first = true;
		BST::printPostOrder(root, first);
		cout << "\n";
	}
	void insert(string name, int id) {
		this->root = BST::helperInsert(this->root, name, id);
	}
	void remove(int id) { //test if you can remove the root
		static bool isHere = false;
		BST::removeID(root, id, isHere);
		if (isHere == true) {
			cout << "Successful\n";
		}
		else {
			cout << "Unsuccessful\n";
		}
		isHere = false;
	}
	void removeInOrder(int num) {
		static bool isHere = false;
		static int count = -1;
		root = BST::removeInorder(root, num, count, isHere);
		count = -1;
		if (isHere == true) {
			cout << "Successful\n";
		}
		else {
			cout << "Unsuccessful\n";
		}
		isHere = false;
	}
	void search(bool isName, string nameOrID) { // to see whether the thing being searched is an ID or a name;
		bool isHere = false;
		if (isName == true) {
			BST::searchName(root, nameOrID, isHere);
		}
		else {
			BST::searchID(root, stoi(nameOrID), isHere);
		}
		if (isHere == false) {
			cout << "Unsuccessful\n";
		}
		isHere = false;
	}
	void printLevelCount() {
		BST::printLevelCount(root);
		cout << "\n";
	}
};


