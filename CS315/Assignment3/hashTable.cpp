// Implementation of hash table
#include "hashTable.h"

hashTable::hashTable() // construct
{
    hashData table[MAX];
}

// hashTable::~hashTable() // destruct
// {
//     for (int i=0; i<MAX; i++)
//     {
//         table[i] = 0;
//     }
// }

void hashTable::addToTable(string w)
{
    int asc = 0;
    for (int i = 0; i < w.length(); i++) // get ascii number for index
    {
        char x = w.at(i);
        asc += int(x);
    }
    if (table[asc].word == "") // check if it's there or not
    {
        table[asc].word = w;
        table[asc].numIn = 1;
    }
    else if (table[asc].word == w)
        table[asc].numIn += 1;
    else
    {  
        bool found = 0;
        for (int j = 0; j < MAX; j++) // look for word if not in correct spot
        {
            if (table[j].word == w)
            {
                table[j].numIn += 1;
                found = 1;
                break;
            }         
        }
        if (found != 1)
        {
            for (int j=0; j<MAX;j++)
            {
                if (table[j].word == "")
                    table[j].word == w;
            }
        }
    }
}

void hashTable::printSorted()
{
    for (int i=0;i<MAX;i++)
    {
        if (table[i].word != "")
            cout << table[i].word << " " << table[i].numIn << endl;
    
    }
}