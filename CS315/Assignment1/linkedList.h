// Implementation of LL for Assignment 1

#include <iostream>
using namespace std;

struct node 
{
    int data;
    float timeData;
    node *next;
};

class linkedList 
{
    public:
        linkedList();
        void insertAtFront(int data, float tData);
        void insertAtRear(int data, float tData);
        int deleteFront();
        int getSize();
        float getTimeData();
    private:
        node *front, *rear;
        int size;
};