#pragma once
#include<fstream>
#include <queue>
#include <string>
#include <sstream>
#include "Trie.h"
using namespace std;

class Trie::DataSaver
{

private:
	fstream* fileStream;
    Trie& trie;
    const string fileName = "Saved-Data.txt";

public:

    DataSaver(Trie& trie) : trie(trie) {
        fileStream = new fstream();
    }

    ~DataSaver() {
        delete fileStream;
    }

    void loadFileData();


    void saveDataToFile();



private:
    void saveRecord(UserData* user);

    void traverse(BranchNode* current, int depth);

    void getStartEndOfTraverse(int& start, int& end, int& depth);

    void split_Line(string line);

    void fillUserAttributes(queue <string> &classAttributes);

};

