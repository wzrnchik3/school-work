Author: William Zrnchik, wjzr222@uky.edu, 02/02/2019

Contents:
    README.txt: this file
    kstring.c: implementation of kstring functions
    kstring.h: header for kstring
    kstring-stubs.c: given kstring.c file
    Makefile: given makefile, updated to include fpic and no-pie flags
    test-abbrev.c: given shortened test file
    test-full.o: given full test file

Running: Can run the test-full by using 'make run' in console using the makefile, 
    along with a valgrind memcheck by using 'make memcheck' in console

Implementation Notes: I used kstralloc() any time I was to allocate memory, instead of using malloc multiple times
    I also used previously made functions as much as possible, such as strlen and strcat

Limitations: No mem leaks or failing cases

References: Dr. Moore's code gave me the idea to use memset and memcpy in my functions 
    Also I had to use the flags given by him to run it as I am using a home Ubuntu system