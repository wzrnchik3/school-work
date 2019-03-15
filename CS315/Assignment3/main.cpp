// main ffunction
#include <iostream>
#include <string> // for string and string functions
#include <fstream> // for ifstream
#include <sstream> // for istringstream
#include "hashTable.h"
using namespace std;

int main() {
    ifstream readIn ("data.test.txt"); // read in file
    string line, word;
    hashTable hash;

    while (getline(readIn, line)) // read in each full line
    {
        for (int i=0, len=line.size();i<len;i++) // replace any punctuation with spaces
        {
            if (ispunct(line[i]))
                line.replace(i, 1, " ");
        }
        istringstream iss(line); // iss can turn the string line into multiple strings
        while (iss >> word) // since all punctuation is spaces, reads line string by string
        {
            hash.addToTable(word); // add the word gotten from the stringstream to hashtable
        }
    }
    readIn.close(); // close infile
    hash.printSorted(); // call the function to print to txt file

    return 0;
}
