/*
 * Course: CS216-00x
 * Project: Lab 10 (as part of Project 2)
 * Purpose: repeatedly ask the user to type prefix to match
 *          then generate at maximum THREE matched terms 
 *          and display the matched terms in descending order by weight.
 ***** PLEASE DO NOT CHANGE THIS FILE *****
 */

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include "term.h"
#include "SortingList.h"
#include "autocomplete.h"

using namespace std;

string removeExtraSpace(string original)
{
    bool hasSpace = true;
    string result;
    for (int i=0; i < original.length(); i++)
    {
        if (original[i] == '\t') // Replaces tabs with blank space
            original[i] = ' ';

        // remove spaces before first non space character and spaces in between that are multiple with one
        if (original[i] != ' ')
        {
            result = result + original[i];
            hasSpace = false;
        }
        else if (!hasSpace)
        {
            result = result + original[i];
            hasSpace = true;
        }
        else
            hasSpace = true;
    }
    return result;
}

int main(int argc, char** argv) {
    const int ARGUMENTS = 3; // changed for extra arg
    int k = atoi(argv[2]); // sets k equal to 3rd arg
    
    // check the command line argument, an input file name is needed
    if (argc != ARGUMENTS)
    {
        cout << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }
    else if (k < 0) // makes sure number is ok
    {
        cout << "The number of matching terms needs to be positive!" << endl;
        return 1;
    }
    
    // check if the input file can be opened successfully
    ifstream infile;
    infile.open(argv[1]);
    if (!infile.good())
    {
        cout << "Cannot open the file named " << argv[1] << endl;
        return 2;
    }  
    
    // read in the terms from the input file
    // line by line and store into Autocomplete object
    Autocomplete autocomplete;
    long weight;
    string query;
    
    while (!infile.eof())
    {
        infile >> weight >> ws;
        getline(infile, query);
        if (query != "")
        {    
            Term newterm(query, weight);
            autocomplete.insert(newterm);
        }    
    } 
    autocomplete.sort();

    string input;
    string prefix;
    cout << "Please input the search query (type \"exit\" to quit): " << endl;
    getline(cin, input);
    prefix = removeExtraSpace(input);
    while (prefix != "exit")
    {
        SortingList<Term> matchedTerms = autocomplete.allMatches(prefix);
        
        if (matchedTerms.size() == 0)
        {    
            cout << "No matched query!" << endl;
        }
        else if (matchedTerms.size() <= k)
            matchedTerms.print();
        else
        {
            for (int i=0; i<k; i++)
                cout << matchedTerms[i] << endl;
        }

        cout << "Please input the search query (type \"exit\" to quit): " << endl;
        getline(cin, input);
        prefix = removeExtraSpace(input); // Removes extra White Space
    }    
    return 0;
}
