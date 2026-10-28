#include <iostream>
#include "HubInventory.h"

using namespace std;

int findHub(const int hubIds[], int size, int targetId)
{
    int matchingIndex = -1; //will be negative one unless we find something.

    if(size == 5)
    {
        for(int i = 0; i < size; i++)
        {
            if(hubIds[i] == targetId)
            {
                 //match at wherever i is!
                matchingIndex = i;
                break;
            }
        else
        {
            //no match THIS TIME
        }
        }
    }
    else
    {
        cout << "Array Size not valid! Not performing search \n";
    }
    //logic goes here
    return matchingIndex;
}

bool reserveKits(int& available, int requested)
{
    bool reservationSuccess = false;
    if(requested > available)
    {
        cout << "Nope. you requested more than are available. not reserving \n";
    }
    else
    {
        //reserve the kits. reduce avaialble kits
        available = available - requested; 
        reservationSuccess = true;
        cout << "kits reserved. now have " << available << " available \n";
    }


    return reservationSuccess;
}