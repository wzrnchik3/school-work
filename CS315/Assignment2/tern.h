// Implementation of ternary tree

#include <iostream>
using namespace std;

struct node 
{
    int lowInt, highInt; // low and high int by value in the node
    node *left, *middle, *right; // pointers to the three nodes left middle and right of the tree
    bool isFull, firstInt; // isFull is false unless node has 2 ints, firstInt is false unless node has 1 int
    node() // constructor sets node pointers to null and bools false
    {
        left, middle, right = NULL;
        isFull, firstInt = false;
    }
    ~node() // destructor
    {
        delete left;
        delete middle;
        delete right;
    }
};

class tern // ternary tree class
{
    public:
        tern(); // constructor
        ~tern(); // deconstructor
        void addInt(int data, node *n); // add into tree
        void printTree(node *n);  // prints systematically
        node ternHead();  // returns head/root of tree
        bool search(int p, node *n); // searches tree
    private:
        node *head; // head or root
};