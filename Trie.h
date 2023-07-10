#pragma once

#include "UserData.h"
#include <string>

class Trie {

private:
	virtual class Node {};
	class BranchNode;
	class FullNode;
	class NodeSpace2;
	class NodeSpace4;
	class NodeSpace9;
	class LeafNode;

	class DataSaver;

private:
	BranchNode* root;

	LeafNode* getLeaf(string id);

	bool isIdValid(string id);

public:


	Trie();

	bool add(UserData* userData);

	bool update(string id, UserData* userData);

	bool remove(string id);
	
	UserData* get(string id);

	void loadData();

	void saveData();
	

};