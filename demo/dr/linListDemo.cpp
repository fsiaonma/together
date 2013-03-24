#include <iostream>
#include <string>
#include "../../src/util/dr/linList.h"
using namespace std;

struct PARAM {
    string key;
    string value;
};

int main() {
    LinList<PARAM> mylist;

    cout << endl;

    cout << "isEmpty:" << endl;
    cout << mylist.isEmpty() << endl << endl;

    PARAM t;
    t.key = "username";
    t.value = "sam";

    cout << "insert:" << endl;
    mylist.insert(t, mylist.getlistSize());
    mylist.insert(t, 8);
    cout << mylist.getlistSize() << endl << endl;

    cout << "getNodeByIndex:" << endl;
    cout << mylist.getNodeByIndex(0)->data.key << '\t'
         << mylist.getNodeByIndex(0)->data.value << endl;
    cout << mylist.getNodeByIndex(8) << endl;
    cout << mylist.getNodeByIndex(-1) << endl << endl;

    cout << "remove:" << endl;
    mylist.remove(0);
    mylist.remove(8);
    cout << mylist.getlistSize() << endl << endl;

    cout << "clear:" << endl;
    for (int i = 0; i < 10; ++i) {
       mylist.insert(t, mylist.getlistSize()); 
    }
    cout << mylist.getlistSize() << endl;
    mylist.clearList();
    cout << mylist.getlistSize() << endl << endl;

    return 0;
}