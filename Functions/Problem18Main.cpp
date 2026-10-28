#include <iostream>
#include "HubInventory.h"

using namespace std;


int main()
{
    int hubIDArray[] = {104, 217, 305, 412, 509};
    int kitCounts[] = {18,   9,  24,   0,  13};

    int enteredHubID;
    int searchResult;
    cout << "Please enter a Hub ID \n";
    cin >> enteredHubID;

    //debugging code
    searchResult = findHub(hubIDArray, 5, enteredHubID);
    if(searchResult == -1)
    {
        cout << enteredHubID << " not found \n";
    }
    else
    {
        cout << enteredHubID << "found at position " << searchResult;
    }

    return 0;
}
