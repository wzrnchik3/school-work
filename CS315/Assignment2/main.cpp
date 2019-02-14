#include <iostream>
#include <fstream>
#include "tern.h"
using namespace std;

int main(int argc, char** argv) {
    tern t; // declare vars
    node ternHead = t.ternHead();
    ifstream infile; // ifstream and string to read in txt file
    string fileName;
    // ask for input files
    cout << "Please enter text file name containing data members to add (default is \"data.ternary.txt\"): ";
    getline(cin, fileName);
    if (fileName != "")
        infile.open(fileName.c_str()); // opens the input file
    else
        infile.open("data.ternary.txt"); // default

    if (!infile.good())
    {
        cout << "Cannot open the file " << fileName << endl;
        return 2;
    }

    int a; // int to be read in from file and read in using while loop
    while (infile >> a)
        t.addInt(a, &ternHead);

    t.printTree(&ternHead); //print out tree
    cout << endl;

    if (argc == 2) // check if an arg was passed, this is my "flag" to put the extra credit search on
    {
        int p; // p will be searched for in tree
        while (true) // loops through until told to break with q or Q
        {
            cout << "Please type a number in to search for inside the tree (Q or q to quit): ";
            cin >> p;
            cin.ignore(256, '\n');

            if (cin.fail()) // if cin doesn't work due to being a string check if q otherwise reloop
            {
                cin.clear();
                string check;
                cin >> check;

                if (check == "q" || check == "Q")
                    break;
                else
                {
                    cout << "Invalid option! Please enter a number." << endl;
                    continue;
                }
                
            }
            if (!t.search(p, &ternHead)) // runs search and prints whether the number was found
                cout << "Number " << p << " not found!\n";
            else if (t.search(p, &ternHead))
                cout << "Number " << p << " was found in the tree\n";
        }
    }

    return 0;
}