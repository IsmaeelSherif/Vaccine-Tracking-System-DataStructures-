#include <string>
#include <assert.h>
#include "Node.h"
#include "Trie.h"
#include "Stats.h"
#include "DataSaver.h"
using namespace std;


#include <iostream>
Trie::Trie()
{
    root = new NodeSpace2(2); //the first number in the Id can only be 2 or 3
    Stats::initialize();
}


bool Trie::add(UserData* userData)
{
    string id = userData->id;

    if (!isIdValid(id))
    {
        return false;
    }

    BranchNode* temp = root;
    Node* nextNode;

    for (int i = 0; i < 13; i++) {
        int charNum = id[i] - '0';
        nextNode = temp->nodeAtIndex(charNum);
        if (nextNode == nullptr)
        {
            nextNode = BranchNode::newNode(i);
            temp->setNodeAtIndex(charNum, nextNode);
        }
        temp = (BranchNode*)nextNode;
    }

    int lastIndex = id[13] - '0';

    //check if leaf already exists
    nextNode = temp->nodeAtIndex(lastIndex);
    LeafNode* leaf = (LeafNode*)nextNode;

    if (leaf != nullptr) {
        return false;
    }

    // add data here to leaf node
    leaf = new LeafNode(userData);
    temp->setNodeAtIndex(lastIndex, leaf);
    Stats::onInsert(userData);

    return true;
}




Trie::LeafNode* Trie::getLeaf(string id) {
    if (!isIdValid(id))
    {
        return nullptr;
    }

    BranchNode* temp = root;
    Node* nextNode;

    for (int i = 0; i < 14; i++) {
        int index = id[i] - '0';
        nextNode = temp->nodeAtIndex(index);
        if (nextNode == nullptr)
        {
            return nullptr;
        }
        temp = (BranchNode*)nextNode;
    }

    LeafNode* leaf = (LeafNode*)nextNode;
    return leaf;
}


bool Trie::isIdValid(string id)
{
    if (id.length() != 14) {
        return false;
    }

    if ((id[0] != '2' && id[0] != '3') || id[3] - '0' > 1 || id[5] - '0' > 3 || id[8] == '0' || id[13] == '0') {
        return false;
    }

    return true;
}



bool Trie::update(string id, UserData* userData) {

    if (!isIdValid(id) || !isIdValid(userData->id))
    {
        return false;

    }
    if (id != userData->id) {
        if (remove(id)) {
            add(userData);
            return true;
        }
        return false;
    }

    LeafNode* leaf = getLeaf(id);

    if (leaf == nullptr) {
        return false;
    }
    Stats::onUpdate(leaf->value, userData);

    leaf->value = userData;
    return true;
}


bool Trie::remove(string id) {
    if (!isIdValid(id))
    {
        return false;
    }

    BranchNode* temp = root;
    Node* nextNode;

    for (int i = 0; i < 13; i++) {
        int index = id[i] - '0';
        nextNode = temp->nodeAtIndex(index);
        if (nextNode == nullptr)
        {
            return false;
        }
        temp = (BranchNode*)nextNode;
    }

    int lastIndex = id[13] - '0';

    //check if leaf exists
    nextNode = temp->nodeAtIndex(lastIndex);
    LeafNode* leaf = (LeafNode*)nextNode;

    if (leaf == nullptr) {
        return false;
    }

    Stats::onDelete(leaf->value);
    temp->setNodeAtIndex(lastIndex, nullptr);
    delete leaf->value;
    delete leaf;
    return true;
}


UserData* Trie::get(string id) {
    LeafNode* leaf = getLeaf(id);
    if (leaf == nullptr) {
        return nullptr;
    }

    return leaf->value;
}








void Trie::loadData() {
    DataSaver* dataSaver = new DataSaver(*this);
    dataSaver->loadFileData();
    delete dataSaver;
}

void Trie::saveData()
{
    DataSaver* dataSaver = new DataSaver(*this);
    dataSaver->saveDataToFile();
    delete dataSaver;
}


