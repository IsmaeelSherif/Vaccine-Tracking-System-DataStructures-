#include "Screen.h"
#include <QtWidgets/QApplication>
#include "Trie.h"
#include "Globals.h"

int main(int argc, char *argv[])
{
    Globals::trie = new Trie;
    Globals::trie->loadData();
    
    QApplication a(argc, argv);
    Screen w;
    w.show();
    return a.exec();
}
