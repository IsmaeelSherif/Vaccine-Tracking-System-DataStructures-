#include "Node.h"


Trie::BranchNode* Trie::BranchNode::newNode(int indexOfIDChar) {

	/*	  2 / 3   | 0 - 9 - 0 - 9 | 0 / 1 | 0 - 9 | 0 - 3 | 0 - 9 | 0 - 3 | 1 - 9 | 0 - 9 | 0 - 9 | 0 - 9 | 0 - 9 |     1 - 9
		thousands |      year     |     month     |      day      |   cityCode    |       birth order today       |   gov interior
		(root)
		*/
	
	BranchNode* nextNode = nullptr;


	switch (indexOfIDChar) {

	case 2:
		nextNode = new NodeSpace2(0);
		break;

	case 7:
	case 12:
		nextNode = new NodeSpace9();
		break;

	case 4:
	case 6:
		nextNode = new NodeSpace4();
		break;

	default:
		nextNode = new FullNode();
	}


	return nextNode;
}


Trie::Node* Trie::FullNode::nodeAtIndex(int index) {
	return nextNodes[index];
}

void Trie::FullNode::setNodeAtIndex(int index, Node* node) {
	nextNodes[index] = node;
}


Trie::Node* Trie::NodeSpace2::nodeAtIndex(int index) {
	return nextNodes[index - baseIndex];
}

void Trie::NodeSpace2::setNodeAtIndex(int index, Node* node) {
	nextNodes[index - baseIndex] = node;
}

Trie::Node* Trie::NodeSpace4::nodeAtIndex(int index) {
	return nextNodes[index];
}

void Trie::NodeSpace4::setNodeAtIndex(int index, Node* node) {
	nextNodes[index] = node;
}

Trie::Node* Trie::NodeSpace9::nodeAtIndex(int index) {
	return nextNodes[index - 1];
}

void Trie::NodeSpace9::setNodeAtIndex(int index, Node* node) {
	nextNodes[index - 1] = node;
}



Trie::LeafNode::LeafNode(UserData* val) {
	value = val;
}