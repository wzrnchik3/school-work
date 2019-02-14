#include <iostream>
#include <cstdlib>
#include "linkedList.h"

float getRandom(float x)
{
    return (x * ((float) rand())/RAND_MAX);
}

int main()
{
    float d = 2.0, p = 2.0, q = 1.0, currentTime = 0.0, maxTime = 10.0;
    int custNum = 0, lineLength = 0;
    linkedList a;

    ///*
    while (currentTime < maxTime)
    {
        //system("read -p 'Press Enter to continue...' var");
        float doorTime = getRandom(d);
        float phoneTime = getRandom(p);
        cout << "CURRENT TIME: " << currentTime << endl; // say current time at beginning of loop
        if (lineLength == 0) // add to line no matter what if line empty
        {
            if (doorTime < phoneTime)
            {
                custNum += 1;
                a.insertAtRear(custNum, getRandom(q));
                currentTime += doorTime;
                lineLength += 1;
                cout << "Customer number " << custNum << " has entered the store at: " << currentTime << ".\n"
                    << "\tThere are currently " << lineLength << " people in line.\n";
            }
            else
            {
                custNum += 1;
                a.insertAtFront(custNum, getRandom(q));
                currentTime += phoneTime;
                lineLength += 1;
                cout << "Customer number " << custNum << " has called the store at: " << currentTime << ".\n"
                    << "\tThere are currently " << lineLength << " people in line.\n";
            }
            
        }
        else
        {
            if (phoneTime < a.getTimeData()) // phone time less than q time
            {
                if (phoneTime < doorTime)
                {
                    custNum += 1;
                    a.insertAtFront(custNum, getRandom(q));
                    currentTime += phoneTime;
                    lineLength += 1;
                    cout << "Customer number " << custNum << " has called the store at: " << currentTime << ".\n"
                        << "\tThere are currently " << lineLength << " people in line.\n";
                }
                else
                {
                    custNum += 1;
                    a.insertAtRear(custNum, getRandom(q));
                    currentTime += doorTime;
                    lineLength += 1;
                    cout << "Customer number " << custNum << " has entered the store at: " << currentTime << ".\n"
                        << "\tThere are currently " << lineLength << " people in line.\n";
                }
                
            }
            else // q time is less than phone time
            {
                if (doorTime < a.getTimeData()) // always do least time option
                {
                    custNum += 1;
                    a.insertAtRear(custNum, getRandom(q));
                    currentTime += doorTime;
                    lineLength += 1;
                    cout << "Customer number " << custNum << " has entered the store at: " << currentTime << ".\n"
                        << "\tThere are currently " << lineLength << " people in line.\n";                    
                }
                else
                {
                    currentTime += a.getTimeData();
                    lineLength -= 1;
                    cout << "Customer number " << a.deleteFront() << " has had their question answered at: " << currentTime << ".\n"
                        << "\tThere are currently " << lineLength << " people in line.\n";
                }
                
            }
            
        }
        
    }
    //*/
    system("read -p 'Press Enter to continue...' var");
    return 0;
}