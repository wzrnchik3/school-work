Author: Will Zrnchik
Contents:
    data.ternary.txt // test data file given
    main.cpp // main function, reads in data and adds it to tree
    makefile // makefile to make and run program
    README.txt // this file
    tern.cpp // implementations of functions for tern class
    tern.h // header for tern class
    test.txt // smaller text file with data to test
Running:
    1. In terminal, navigate to the correct directory
    2. 
        a. To only compile the executable file type the command 'make' in the command line
        b. To compile and run the program type 'make run' in the command line
        c. To compile and run the program with the extra credit search function type 'make search'
    3. 
        a. While the program is runnning it will ask you which file you would like to read from
            If you decide to use the data.ternary.txt file just press enter and it will input that 
            by default
        b. If you decide to run with the search function, it will first ask you to type in the
            file you would like to use, again just press enter for default data.ternary.txt file.
            After this is done and it prints out the tree, the program will continue and ask you
            to type a number in to search through the tree. It will continue to ask you until you 
            press q or Q to quit the program.
    4. Type 'make clean' in terminal to get rid of program and object files.
Implementation Notes: 
    Has constructors and destructors, all heap blocks freed, no leaks possible
Limitations:
    Has memory errors, specifically "Uninitialised value was created by a heap allocation",
        and "Conditional jump or move depends on Uninitialised value(s)". Have tried multiple things
        however cannot find a fix. I believe the amount of errors was less before I created the destructors
        but there were memory leaks.
Extra Credit:
    1. Implemented a search function, 2c in the running section. Or 'make search'