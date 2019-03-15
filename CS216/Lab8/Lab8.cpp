/* Course: CS216-00x
 * Project: Lab 8
 * Purpose: Provide the user to repeatedly choose one option to sort the list of buildings of the University of Kentucky
 *          until the user clicks "Q" or "q" to quit
 *          option 1: list the buildings in its original order reading from a file
 *          option 2: list the buildings in dictionary order by buildings' names
 *          option 3: list the buildings in ascending order by buildings' IDs (four-digit number, may contain extra leading zero)
 *          option 4: list the buildings in reverse dictionary order by buildings' coordinates in the map)
 *Author: Will Zrnchik
 */ 

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "building.h"
#include "BuildingList.h"

using namespace std;

int main(int argc, char* argv[]) { 
    ifstream in_file;

    // Check if missing command line argument
    if (argc != 2)
    {
        cout << "Missing one command line argument!" << endl;
        cout << "Usage: " << argv[0] << " input_filename" << endl;
        return 1;
    }

    // Check if opening the file successfully
    in_file.open(argv[1]);
    if (in_file.fail())
    {
        cout << "Failure in opening file: " << argv[1] << endl;	
        return 2;
    }

    // Read data from the file and store into the SortingList object
    // Assume "good data" from the file
    BuildingList UKY_buildingList;
    string line;  // to store each complete text line from the file
    while (!in_file.eof())
    {
        getline(in_file, line);
        string name, position;
        int ID;
        istringstream iss(line);
        getline(iss, name, '\t');

        // separate the rest part into ID and coordinate in the map, and also extra white space
        iss >> ws >> ID >> ws >> position;

        if (name != "")
        {    
            Building newbuilding(name, ID, position);
            UKY_buildingList.insert(newbuilding);
        }    
    }    
    // close the file after finishing reading data from
    in_file.close(); 

    int option;
    while (true)
    {
        cout << endl;
        cout << "This application stores information about buildings of University of Kentucky." << endl;
        cout << "To sort the buildings in different orders, please choose your option (Enter Q or q to quit):" << endl;
        cout << "1. its order reading from the file" << endl;
        cout << "2. dictionary order by buildings' names" << endl;
        cout << "3. non-descending order by buildings' IDs (four-digit)" << endl;
        cout << "4. reverse dictionary order by buildings' coordinates in the map" << endl;

        cin >> option;
        cin.ignore(256, '\n');

        if (cin.fail())
        {
            string input_to_check;
            cin.clear();
            cin >> input_to_check;
            if (input_to_check == "Q" || input_to_check == "q")
                break;
            else
            {
                cout << "Invalid option!" << endl;
                continue;
            }
        }

        switch (option)
        {
            case 1: {   cout << "Buildings are in its order reading from the file: "<< endl;
                        UKY_buildingList.print();
                        break;
                    }
            case 2: {   cout << "Buildings are in dictionary order by buildings' names: " << endl;
                        // Your code starts here
                        break;
                    }
            case 3: {   cout << "Buildings are in non-descending order by buildings' IDs: " << endl;
                        // Your code starts here
                        break;
                    }
            case 4: {   cout << "Buildings are in reverse dictionary order by buildings' coordinates: " << endl;
                        // Your code starts here
                        break;
                    }
            default:
                    cout << "Invalid option!" << endl;
        }
    }
    cout << "Thank you for using my program, bye..." << endl;
    return 0;
}

