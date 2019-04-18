#include "famTree.h"
#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    famTree f;
    string filename, command, inStr;
    int pNum, pNum2, fNum, parent, marriage, husband, wife, childArray[MAX_CHILDREN];
    bool needCommand = true;
    for (int i = 0; i < MAX_CHILDREN; i++)
        childArray[i] = -1;
    ifstream infile;
    infile.open("test.txt");
    while (!infile.eof())
    {
        if (needCommand)
            infile >> command;
        if (command == "Insert")
        {
            infile >> pNum >> inStr >> parent >> inStr >> marriage;
            f.insert(pNum, parent, marriage);
            needCommand = true;
        }
        else if (command == "Check")
        {
            f.check();
            needCommand = true;
        }
        else if (command == "Relate")
        {
            infile >> pNum >> pNum2;
            cout << pNum << pNum2;
            f.relate(pNum, pNum2);
            needCommand = true;
        }
        else if (command == "Family")
        {
            infile >> fNum >> inStr >> husband >> inStr >> wife >> inStr;
            int numC = 0;
            while (inStr == "Child")
            {
                infile >> childArray[numC] >> inStr;
                numC += 1;
            }
            f.family(fNum, husband, wife, childArray, numC);
            command = inStr;
            needCommand = false;
        }
    }
    return 0;
}