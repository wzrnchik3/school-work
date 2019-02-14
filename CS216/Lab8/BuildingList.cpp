/* File: BuildingList.cpp
 * Course: CS216-00x
 * Project: Lab 8
 * Purpose: provide the implementation of the member functions for the class named BuildingList
 *
 */
#include <cassert>
#include "BuildingList.h"

// default constructor
BuildingList::BuildingList()
{
    //you do not need to do anything
    //since vector class provides default constructor to create an empty vector object
}

// insert a new Building object: newBuilding
// it is inserted at the end of the current vector
void BuildingList::insert(Building newBuilding)
{
    buildings.push_back(newBuilding);
}

// return how many Building objects currently in the vector
int BuildingList::Size() const
{
    return buildings.size();
}

// return reference to a Building object at index of x
Building &BuildingList::Element(int x)
{
    assert(x >= 0 && x < this->Size());
    return buildings[x];
}
    
// display the sequence of Building objects one by one
// indirectly calling print() function from Building class
void BuildingList::print() const
{
    for (int x = 0; x < this->Size(); x++)
    {
        buildings[x].print();
    }
}

// apply bubble_sort algorithm
// return a BuildingList object which contains the elements in lexicographical order by building name
BuildingList BuildingList::sort_by_Name()
{
    BuildingList result = *this;
    int size = this->Size();
    Building temp;   // for swapping

    for (int i = 0 ; i < size-1 ; i++)
    {
        for (int j = 0 ; j < size-1 ; j++)
        {
            if ( result.buildings[j].compareByName(result.buildings[j+1]) <0 )
            {
                temp = result.buildings[j];
                result.buildings[j] = result.buildings[j+1];
                result.buildings[j+1] = temp;
            }        
        }
    }
    return result;
}

// apply ??? sorting algorithm (you choose)
// return a BuildingList object which contains the elements in ascending order by building ID (four-digit number, may contain extra leading zero)
BuildingList BuildingList::sort_by_ID()
{
    // your code starts here
}

// apply ??? sorting algorithm (you choose)
// return a BuildingList object which contains the elements in reverse lexicographical order by building coordinate
BuildingList BuildingList::sort_by_Reverse_Coordinate()
{
    // your code starts here
}

