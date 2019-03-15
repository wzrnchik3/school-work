Author: 
    William Zrnchik
Contents: 
    data.hashing.txt // original txt data given
    data.test.txt // test txt 
    hashTable.cpp // Implementation of hashTable class
    hashTable.h // header/ declaration of class
    main.cpp // main program calls hashtable class
    makefile
    output.hashing.txt // output of data from data.hashing.txt
    output.test.txt // same as above but for test
    README.txt // this file
Running:
    If needing to change in file or outfile must change manually, in file read
    in main.cpp while the outfile is in the printSorted() method in hashTable.cpp.

    To simply run, you can use the makefile by typing "make run" in terminal under the
    correct directory.

    To just compile, type "make" in terminal under the correct directory.

    To clean object files, "make clean" in terminal under the directory.
Implementation Notes:
    Used heapsort, looks a little sloppy using some sort algorithms inside
    of the print function but it seemed to be the easiest way to sort both
    alphabetically and numerically and print out in one function.
Limitations: 
    None I can see, other than trying to hash a data set larger than the MAX set
    value of 1000.
References:
    Brady Hoeper, friend
    cplusplus.com Doc Pages
    geeksforgeeks.com