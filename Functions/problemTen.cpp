#include <iostream>

using namespace std;

void addDeliveredKits(int& storedKits, int deliveredKits)
{
   
    //int theTotal = storedKits + deliveredKits;
    storedKits += deliveredKits;

}

int main()
{
    int currentStoredCount;
    int newlyDeliveredCount;
    cout << "What is the current stored count? \n";
    cin >> currentStoredCount;
    cout << "What is the newly delivered count? \n";
    cin >> newlyDeliveredCount;
    addDeliveredKits(currentStoredCount, newlyDeliveredCount);

    cout << "updated count is " << currentStoredCount;

    return 0;
}

