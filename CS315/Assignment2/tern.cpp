// Implementation of ternary tree class
#include "tern.h"

tern::tern() // constructor, makes new head node
{
    head = new node; 
}

tern::~tern() // destructor
{
    delete head;
}

void tern::addInt(int data, node *n) // adds an integer to the tree
{
    if (!n->isFull) // checks if the node is full
    {
        if (!n->firstInt) // checks if the node has had any ints entered yet (fix for 0 or -1)
        {
            n->lowInt = data;
            n->firstInt = true;
        }    
        else if (n->lowInt <= data) // puts data int into correct position in the node
        {
            n->highInt = data;
            n->isFull = true;
        }
        else if (n->lowInt >= data) 
        {
            n->highInt = n->lowInt;
            n->lowInt = data;
            n->isFull = true;
        }
    }
    else // if node isFull checks if the left middle or right has a node and puts it there, if node doesnt exist make new
    {
        if (data <= n->lowInt) 
        {
            if (n->left == NULL) 
            {
                node *newN = new node;
                n->left = newN;
                addInt(data, newN);
            }
            else
                addInt(data, n->left);
        }
        else if (n->lowInt < data && data <= n->highInt)
        {
            if (n->middle == NULL)
            {
                node *newN = new node;
                n->middle = newN;
                addInt(data, newN);
            }
            else
                addInt(data, n->middle);
            
        }
        else
        {
            if (n->right == NULL)
            {
                node *newN = new node;
                n->right = newN;
                addInt(data, newN);
            }
            else
                addInt(data, n->right);
            
        }
        
    }
}

void tern::printTree(node *n) // print tree systematically (left) low (middle) high (right)
{
    if (n->left != NULL)
    {
        cout << "(";
        printTree(n->left);
        cout << ")";
    }
    cout << " " << n->lowInt << " ";
    if (n->middle != NULL)
    {
        cout << "(";
        printTree(n->middle);
        cout << ")";
    }
    if (n->isFull)
        cout << " " << n->highInt << " ";
    if (n->right != NULL)
    {
        cout << "(";
        printTree(n->right);
        cout << ")";
    }
}

node tern::ternHead() // return the head/root of ternary tree
{
    return *head;
}

bool tern::search(int p, node *n) // search for int p in the ternary tree
{
    if (!n->isFull) // if not full, only has to check lowInt
    {
        if (p == n->lowInt)
            return 1;
        else
            return 0;
    }
    else // if full checks both
    {    
        if (p == n->lowInt || p == n->highInt) // if found return 1 or true
            return 1;
        else
        {
            if (p < n->lowInt && n->left != NULL) // if less than p check left node next, if no left node, return 0
                return search(p, n->left);
            else if (p < n->lowInt && n->left == NULL)
                return 0;
            
            if (p > n->lowInt && p < n->highInt && n->middle != NULL) // same for middle node
                return search(p, n->middle);
            else if (p > n->lowInt && p < n->highInt && n->middle == NULL)
                return 0;
            
            if (p > n->highInt && n->right != NULL) // same for right node
                return search(p, n->right);
            else if (p > n->highInt && n->right == NULL)
                return 0;
        }
        
    }
    
}