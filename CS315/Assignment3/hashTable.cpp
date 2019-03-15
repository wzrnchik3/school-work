// Implementation of hash table
#include "hashTable.h"

hashTable::hashTable() // construct
{
    hashData table[MAX];
}

void hashTable::addToTable(string w) // add a string to hash table
{
    int asc = 0;
    for (int i = 0; i < w.length(); i++) // get ascii number for index as hash value
    {
        char x = w.at(i);
        asc += int(x);
    }
    if (table[asc].word == "") // check if it's there or not
    {
        table[asc].word = w;
        table[asc].numIn = 1;
    }
    else if (table[asc].word == w) // if there add 1 to number in table
        table[asc].numIn += 1;
    else // if ascii value index is taken first make sure no where else
    {  
        bool found = 0;
        for (int j = 0; j < MAX; j++) // look for word if not in correct spot
        {
            if (table[j].word == w) // if word exists in table add to num val
            {
                table[j].numIn += 1;
                found = 1;
                break; // break for loop if found
            }        
            //break;

        }
        if (found != 1) // if not found put in first available spot
        {
            for (int j=0; j<MAX;j++)
            {
                if (table[j].word == "")
                {
                    table[j].word = w;
                    table[j].numIn = 1;
                    break;
                }    
            }
        }
    }
}

void hashTable::sortIndexA(hashData array[], int size, int root) // sort alphabetical
{
    int big = root; // set biggest as root index
    int right = 2*root +2; // get right node index
    int left = 2*root +1; // get left node index

    if (left < size && array[left].word > array[big].word) // if left node larger make it the biggest
        big = left;

    if (right < size && array[right].word > array[big].word) // same as above for right
        big = right;

    if (big != root) // if the root and the biggest are not the same swap
    {
        swap(array[root], array[big]);
        sortIndexA(array, size, big); // run heapify again
    }
}

// all same as alphabetical heapify above except comparing number of uses
int hashTable::sortIndexN(hashData array[], int size, int root)
{
    int big = root;
    int right = 2*root +2;
    int left = 2*root +1;

    if (left < size && array[left].numIn < array[big].numIn)
        big = left;

    if (right < size && array[right].numIn < array[big].numIn)
        big = right;

    if (big != root)
    {
        swap(array[root], array[big]);
        sortIndexN(array, size, big);
    }
}

void hashTable::printSorted() // print to txt file, doubles as calling sort
{
    ofstream oFile ("output.tst.txt"); // open out stream
    for (int i = MAX/2 - 1; i >=0; i--) // start heap sort alphabetically
        sortIndexA(table, MAX, i); // build heap by rearranging array

    for (int j = MAX-1; j >=0; j--) // extract ele from heap
    {
        swap(table[0], table[j]); // curr root to end
        sortIndexA(table, j, 0); // heapify
    }

    for (int i=0;i<MAX;i++) // print to file
    {
        if (table[i].word != "")
            oFile << table[i].word << " " << table[i].numIn << endl;            
    }


    for (int i = MAX/2 - 1; i >=0; i--) // heapsort same as above except numerical
        sortIndexN(table, MAX, i);

    for (int j = MAX-1; j >=0; j--)
    {
        swap(table[0], table[j]);
        sortIndexN(table, j, 0);
    }

    oFile << "\n"; // extra line in between
    for (int i=0;i<MAX;i++) // print to file
    {
        if (table[i].word != "")
            oFile << table[i].word << " " << table [i].numIn << endl;
    }
    oFile.close(); // close file
}