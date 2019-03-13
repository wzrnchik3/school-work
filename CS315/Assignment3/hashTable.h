// Definition of hash table

#include <string>
#include <iostream>
using namespace std;
int const MAX = 1000;

struct hashData
{
    string word; // word being hashed
    int numIn; // num of words in chain
    hashData() // constructors
    {
        word = "";
        numIn = 0;
    }
};

class hashTable // hash table class
{
    public:
        hashTable();
        //~hashTable();
        void addToTable(string w);
        int sortIndexA();
        int sortIndexN();
        void printSorted();
    private:
        hashData table[MAX];
};
