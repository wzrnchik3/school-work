// main ffunction
#include <iostream>
#include <string>
#include "hashTable.h"
using namespace std;

int main() {
    string a = "hi";
    string b = "blue";
    string c = "green";
    hashTable hT;

    hT.addToTable(a);
    hT.addToTable(b);
    hT.addToTable(c);

    hT.printSorted();

    return 0;
}
