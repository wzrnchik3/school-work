// Definition of hash table

#include <string>
#include <iostream>
#include <fstream> // for ofstream
using namespace std;
int const MAX = 1000; // was a big enough array for hashing

struct hashData // data being stored in table
{
    string word; // word being hashed
    int numIn; // num of words in chain
};

class hashTable // hash table class
{
    public:
        hashTable();
        void addToTable(string w);
        void sortIndexA(hashData array[], int size, int root);
        int sortIndexN(hashData array[], int size, int root);
        void printSorted();
    private:
        hashData table[MAX]; // the hash table
};
