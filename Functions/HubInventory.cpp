#include <iostream>
#include "HubInventory.h"

int findHub(const int hubIds[], int size, int targetId)
{
    int matchingIndex = -1; //will be negative one unless we find something.

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

    //logic goes here
    return matchingIndex;
}

bool reserveKits(int& available, int requested)
{
    //logic goes here
    return false;
}