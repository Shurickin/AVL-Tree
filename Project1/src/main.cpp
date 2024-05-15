#include <sstream>
#include <cstring>
#include "TreeNode.h"
#include "BST.h"

string verifyNextWord(istringstream& in) { // returns the word if it is valid
	string word;
	in >> word; //read in next word

	if (word.length() > 20) {
		return "";
	}

	for (char c : word) {
		if (!isalpha(c) && !isdigit(c)) {
			return "";
		}
	}

	return word;
}

bool verifyInput(string nameOrid) {
	for (char c : nameOrid) {
		if (!isalpha(c) && !isdigit(c)) {
			if(c != '"')
				return false;
		}
	}
	return true;
}

int main() {
	BST bst;
	bool valid = false;
	int numberOfCommands = 0;

	cin >> numberOfCommands;
	for (int i = 0; i <= numberOfCommands; i++) { // runs for the appropriate number of commands
		string line;

		getline(cin, line);// reads one line of input
		istringstream in(line); //creates an input stream from line

		string command;
		getline(in, command, ' '); // gets the command from input stream\

		string name;
		getline(in, name, ' '); // read up to next qutoation mark, 

		string id;
		getline(in, id); // read the rest of the line, gets id ****SEE IF IT MAY BE BETTER TO KEEP ID AS A STRING*****

		if (_strcmpi(command.c_str(), "insert") == 0) {
			if (verifyInput(name) == false || verifyInput(id) == false) { // checks if name and id's characters are in the alphabet and if its a number, respectively
				cout << "Unsuccessful\n";
			}
			else if (id.length() < 8 || id.length() > 8) {
				cout << "Unsuccessful\n";
			}
			else {
				bst.insert(name, stoi(id));
			}
		}
		else if (_strcmpi(command.c_str(), "printInorder") == 0) {
			bst.printInOrder();
		}
		else if (_strcmpi(command.c_str(), "printPreOrder") == 0) {
			bst.printPreOrder();
		}
		else if (_strcmpi(command.c_str(), "printPostOrder") == 0) {
			bst.printPostOrder();
		}
		else if (_strcmpi(command.c_str(), "remove") == 0) {// id value should be in the name variable
			bst.remove(stoi(name));
		}
		else if (_strcmpi(command.c_str(), "removeInorder") == 0) { // num val should be in name
			bst.removeInOrder(stoi(name));
		}
		else if (_strcmpi(command.c_str(), "search") == 0) { // name or id will be in name
			bool isName = true;
			for (char c : name) {
				if (!isalpha(c)) {
					if (c != '"')
						isName = false;
					
				}
			}
			bst.search(isName, name);
		}
		else if (_strcmpi(command.c_str(), "printLevelCount") == 0) {
			bst.printLevelCount();
		}

	}

	return 0;
}