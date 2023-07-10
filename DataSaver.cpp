#include "DataSaver.h"
#include "Node.h"

void Trie::DataSaver::loadFileData()
{
    string line;
    fileStream->open(fileName, ios::in);
    while (!fileStream->eof()) {
        getline(*fileStream, line);
        split_Line(line);
    }
    fileStream->close();
}

void Trie::DataSaver::split_Line(string line)
{
    string temp;
    queue<string> classAttributes;   // queue to push each word in the Line separated
    stringstream ss(line);
    while (ss >> temp)  // separates Line by delimiter ' '
        classAttributes.push(temp);
    fillUserAttributes(classAttributes);
}

void Trie::DataSaver::fillUserAttributes(queue<string> &userAttributes)
{
    if (userAttributes.empty()) {
        return;
    }

    UserData* user = new UserData();

    //Fill UserData members
    user->id = userAttributes.front();
    userAttributes.pop();
    user->password = userAttributes.front();
    userAttributes.pop();
    user->firstName = userAttributes.front();
    userAttributes.pop();
    user->lastName = userAttributes.front();
    userAttributes.pop();
    user->isMale = stoi(userAttributes.front());
    userAttributes.pop();
    user->age = stoi(userAttributes.front());
    userAttributes.pop();
    user->governorate = userAttributes.front();
    userAttributes.pop();
    user->doseCount = stoi(userAttributes.front());
    userAttributes.pop();

    trie.add(user);
}

void Trie::DataSaver::saveDataToFile()
{
    fileStream->open(fileName, ios::out);
    traverse(trie.root, 0);
    fileStream->close();
}


void Trie::DataSaver::saveRecord(UserData* user)
{
    *fileStream << user->id << " " << user->password << " " << user->firstName << " " << user->lastName << " "
        << user->isMale << " " << user->age << " " << user->governorate << " " << user->doseCount << endl;
}

void Trie::DataSaver::traverse(BranchNode* currentNode, int depth)
{

    int start = 0, end = 0;
    getStartEndOfTraverse(start, end, depth);

    Node* nextNode;
    for (int i = start; i <= end; i++)
    {
        nextNode = currentNode->nodeAtIndex(i);
        if (nextNode == nullptr)
        {
            continue;
        }
        if (depth == 13)
        {
            saveRecord(((LeafNode*)nextNode)->value);
        }

        else {
            traverse((BranchNode*)nextNode, depth + 1);
        }

    }
}

void Trie::DataSaver::getStartEndOfTraverse(int& start, int& end, int& depth)
{
    switch (depth)
    {
    case 0:
        start = 2, end = 3;
        return;
    case 3:
        start = 0, end = 1;
        return;
    case 5:
    case 7:
        start = 0, end = 3;
        return;
    case 8:
    case 13:
        start = 1, end = 9;
        return;
    default:
        start = 0, end = 9;
        return;
    }
}