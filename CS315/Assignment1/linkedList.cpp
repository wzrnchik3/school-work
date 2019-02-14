#include "linkedList.h"

linkedList::linkedList() // constructor
{
    front = NULL;
    rear = NULL;
    size = 0;
}

void linkedList::insertAtFront(int data, float tData)
{
    node *n = new node;
    n->data = data;
    n->timeData = tData;
    if (front == NULL) // if front empty begin filling list
    {
        n->next = NULL;
        front = n;
        rear = n;
        //delete n;
    }
    else // link new node to front of the list
    {
        n->next = front;
        front = n;
        //delete n;
    }
    size += 1;
}

void linkedList::insertAtRear(int data, float tData)
{
    node *n = new node;
    n->data = data;
    n->timeData = tData;
    if (rear == NULL) // check if list is empty and init if it is
    {
        n->next = NULL;
        front = n;
        rear = n;
        //delete n;
    }
    else // point current rear to new rear
    {
        n->next = NULL;
        rear->next = n;
        rear = n;
        //delete n;
    }
    size += 1;    
}

int linkedList::deleteFront()
{
    if (front == NULL) // if empty return -1 as error
        return -1;
    node *temp = front->next; //set a temp node as next
    int custData = front->data;
    if (front == rear)
    {
        front = NULL;
        rear = NULL;
        size -= 1;
        return custData;
    }
    delete front;
    front = temp;
    //delete temp;
    size -= 1;
    return custData;
}

int linkedList::getSize()
{
    return size;
}

float linkedList::getTimeData()
{
    return front->timeData;
}