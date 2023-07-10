#pragma once
using namespace std;

#include "Trie.h"
#include "UserData.h"


class Trie::BranchNode : public Node {

protected: BranchNode() {}

public:

    static BranchNode* newNode(int indexOfIDChar);

    virtual Node* nodeAtIndex(int index) = 0;

    virtual void setNodeAtIndex(int index, Node* node) = 0;
};


class Trie::FullNode : public BranchNode {

private:
    Node* nextNodes[10];


public:

    FullNode() {
        for (int i = 0; i < 10; i++) {
            nextNodes[i] = nullptr;
        }
    }

    Node* nodeAtIndex(int index);

    void setNodeAtIndex(int index, Node* node);

};



class Trie::NodeSpace2 : public BranchNode {

private:

    int baseIndex;
    Node* nextNodes[2];

public:

    NodeSpace2(int baseIndex) {
        this->baseIndex = baseIndex;
        for (int i = 0; i < 2; i++) {
            nextNodes[i] = nullptr;
        }
    }

    Node* nodeAtIndex(int index);

    void setNodeAtIndex(int index, Node* node);
};



class Trie::NodeSpace4 : public BranchNode {

private:

    Node* nextNodes[4];

public:

    NodeSpace4() {
        for (int i = 0; i < 4; i++) {
            nextNodes[i] = nullptr;
        }
    }

    Node* nodeAtIndex(int index);

    void setNodeAtIndex(int index, Node* node);
};


class Trie::NodeSpace9 : public BranchNode {

private:

    Node* nextNodes[9];

public:

    NodeSpace9() {
        for (int i = 0; i < 9; i++) {
            nextNodes[i] = nullptr;
        }
    }

    Node* nodeAtIndex(int index);

    void setNodeAtIndex(int index, Node* node);
};


class Trie::LeafNode : public Node {

public:
    UserData* value;

    LeafNode(UserData* val);
};
