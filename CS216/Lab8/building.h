/* File: building.h
 * Course: CS216-00x
 * Project: Lab 8
 * Purpose: provide the declaration of the class named Building
 *** DO NOT CHANGE THIS FILE ***
 *
 */

#ifndef BUILDING_H
#define	BUILDING_H

#include <iostream>
#include <string>

using namespace std;

const int DIGITS = 4;  // building ID contains exact 4 digits (extra leading 0 may be used to match 4 digits)

class Building
{
    public:
        // default constructor
        Building();

        // alternate constructor
        Building(string name, int id, string position);
        
        // return the current value of name
        string get_Name() const;
        
        // return the current value of ID
        int get_ID() const;

        // return the current value of coordinate
        string get_Coordinate() const;

        // compare with another Building object passed in as parameter: other
        // if the names of this object and other object are in lexicographical order, return 1;
        // if the names of this ojbect and other object are the same, return 0;
        // otherwise, return -1
        int compareByName(const Building& other) const;

        // compare with another Building object passed in as parameter: other
        // if the ID of this object is lower than that of other object, return 1;
        // if the ID of this ojbect is higher than that of other object return -1;
        // otherwise, return 0
        int compareByID(const Building& other) const;

        // compare with another Building object passed in as parameter: other
        // if the coordinates of this object and other object are in reversed lexicographical order, return 1;
        // if the names of this ojbect and other object are the same, return 0;
        // otherwise, return -1
        int compareByReverseCoordinate(const Building& other) const;

        // display the current value of the data members to the screen in such format:
        // name (ID: four-digit ID) ---> coordinate
        void print() const;

    private:
        string name;        // building name
        int ID;             // building ID, which is four-digit number (with possible extra leading 0)
        string coordinate;  // building coordinate in the map(e.g., E5)  
};

#endif	/* BUILDING_H */

