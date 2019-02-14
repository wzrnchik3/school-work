/* File: building.cpp
 * Course: CS216-00x
 * Project: Lab 8
 * Purpose: provide the implementation of the member functions for the class named Building
 *
 */

#include <iomanip>  // std:setw; std::setfill
#include "building.h"

// default constructor
Building::Building()
{
    ID = 0;
}

// alternate constructor
Building::Building(string name, int ID, string coordinate)
{
    this->name = name;
    this->ID = ID;
    this->coordinate = coordinate;
}

// return the current value of name
string Building::get_Name() const
{
    return name;
}

// return the current value of ID
int Building::get_ID() const
{
    return ID;
}

// return the current value of coordinate
string Building::get_Coordinate() const
{
    return coordinate;
}

// compare with another Building object passed in as parameter: other
// if the names of this object and other object are in lexicographical order, return 1;
// if the names of this ojbect and other object are the same, return 0;
// otherwise, return -1
int Building::compareByName(const Building& other) const
{
    if (this->name < other.name)
        return 1;
    if (this->name == other.name)
        return 0;
    else 
        return -1;
}

// compare with another Building object passed in as parameter: other
// if the ID of this object is lower than that of other object, return 1;
// if the ID of this ojbect is higher than that of other object return -1;
// otherwise, return 0
int Building::compareByID(const Building& other) const
{
    // your code starts here
    if (this->ID < other.ID)
        return 1;
    else if (this-> other.ID)
        return -1;
    else
        return 0;
}

// compare with another Building object passed in as parameter: other
// if the coordinates of this object and other object are in reversed lexicographical order, return 1;
// if the names of this ojbect and other object are the same, return 0;
// otherwise, return -1
int Building::compareByReverseCoordinate(const Building& other) const
{
    // your code starts here
    if (this->coordinate < other.coordinate) 
       return 1;
    else if (this->coordinate == other.coordinate)
	    return 0;
    else
	    return -1;
}

// display the current value of the data members to the screen in such format:
// name (ID: four-digit ID) ---> coordinate
void Building::print() const
{
    cout << this->name << "\t( ID: " << setfill('0') << setw(DIGITS) << this->ID << " ) ---> " << this->coordinate << endl; 
}

