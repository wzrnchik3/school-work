/* File: autocomplete.h
 * Course: CS216-00x
 * Project: Lab10 (as part of Project 2)
 * Purpose: the implementation of member functions for the class named Autocomplete.
 *
 */
#include <iostream>
#include "autocomplete.h"

// default constructor
Autocomplete::Autocomplete()
{    
}


// inserts the newterm to the sequence
// note that a SortingList<Term> object, named terms
//          represents the sequence
void Autocomplete::insert(Term newterm)
{
    // your code starts here    
    terms.insert(newterm);
}


// sort all the terms by query in the lexicographical order  
void Autocomplete::sort()
{
    // your code starts here
    terms.sort();
    
}

// binary search helper function
// as private function
// since it serves binary_search member function only
int Autocomplete::binary_searchHelper(SortingList<Term> terms, string key, int left_index, int right_index)
{
    // your code starts here
    int searchIndex = (left_index + right_index)/2;
    if (left_index == right_index){
        return -1;
    }
    if (right_index >= left_index){
        if (terms[searchIndex].query.substr(0, key.length()) == key)
            return searchIndex;
        if (terms[searchIndex].query.substr(0, key.length()) > key)
            return binary_searchHelper(terms, key, left_index, searchIndex-1);
        if (terms[searchIndex].query.substr(0, key.length()) < key)
            return binary_searchHelper(terms, key, searchIndex+1, right_index);
    }
}

// return the index number of the term whose query 
// prefix-matches the given prefix, using binary search algorithm
// Note that binary search can only be applied to sorted sequence
// Note that you may want a binary search helper function
int Autocomplete::binary_search(string prefix)
{
    return binary_searchHelper(terms, prefix, 0, terms.size()-1);
}

// first: the index of the first query whose prefix matches
//          the search key, or -1 if no such key
// last: the index of the last query whose prefix matches 
//         the search key, or -1 if no such key
// key: the given prefix to match
// hints: you can call binary_search() first to find one matched index number,
//        say hit, then look up and down from hit, to find first and last respectively
void Autocomplete::search(string key, int& firstIndex, int& lastIndex)
{
    int found_pos = binary_search(key);
    if (found_pos == -1)
    {
        firstIndex = -1;
        lastIndex = -1;
    }
    else
    {
        // Please note that the following block of code is for Lab10 only
        // you need to replace it for Project 2
        firstIndex = found_pos;
        lastIndex = found_pos;
        int r = key.length();
        
        // starting with found_pos
        // look forwards and backwards to find other possible prefix-matched terms
        int i = found_pos;

        // looking forwards
        i--;
        if (i >= 0 && Term::compareByPrefix(terms[found_pos],terms[i], r) == 0)
        firstIndex = i;

        // looking backwards;
        i = found_pos;
        i++;
        if (i < terms.size() && Term::compareByPrefix(terms[found_pos],terms[i], r) == 0)
        lastIndex = i;
    }
}

// returns all terms that start with the given prefix, in descending order of weight
SortingList<Term> Autocomplete::allMatches(string prefix)
{
    SortingList<Term> match;
    int firstIndex = 0; 
    int lastIndex = 0;
    search(prefix, firstIndex, lastIndex);
    if (firstIndex == -1 || lastIndex == -1)
        return match;
    for (int i = firstIndex; i <= lastIndex; i++)
        match.insert(terms[i]);

    // sorts the terms by weight using ??? sorting algorithm
    
    // your code starts here
    match.bubble_sort(Term::compareByWeight);


    return match;        
}

void Autocomplete::print()
{
    terms.print();
}
