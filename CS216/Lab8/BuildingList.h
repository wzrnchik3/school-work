/* File: BuildingList.h
 * Course: CS216-00x
 * Project: Lab 8
 * Purpose: provide the declaration of the class named BuildingList
 *** DO NOT CHANGE THIS FILE ***
 *
 */

#ifndef BUILDINGLIST_H
#define	BUILDINGLIST_H

#include <iostream>
#include <vector>
#include "building.h"

using namespace std;

class BuildingList
{
    public:
    // default constructor
    BuildingList();
    
    // insert a new Building object: newBuilding
    // it is inserted at the end of the current vector
    void insert(Building newBuilding);     
        
    // return how many Building objects currently in the vector
    int Size() const;

    // return reference to an element at index of x
    Building &Element(int x);        
    
    // display the sequence of Building objects one by one
    void print() const;

    // apply bubble_sort algorithm
    // return a BuildingList object which contains the elements in lexicographical order by building name
    BuildingList sort_by_Name();
    
    // apply ??? sorting algorithm (you choose)
    // return a BuildingList object which contains the elements in ascending order by building ID (four-digit number, may contain extra leading zero)
    BuildingList sort_by_ID();
    
    // apply ??? sorting algorithm (you choose)
    // return a BuildingList object which contains the elements in reverse lexicographical order by building coordinate
    BuildingList sort_by_Reverse_Coordinate();
        
    private:
        vector<Building> buildings;         // a vector of Building objects
};

#endif	/* SORTINGLIST_H */

