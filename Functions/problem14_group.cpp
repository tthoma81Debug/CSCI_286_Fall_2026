#include <iostream>

using namespace std;



void addReserveKits(int kits[], int size, int extraPerHub)
{
    for(int i = 0; i < size; i++)
    {
        kits[i] += extraPerHub;
    }
}

int calculateTotalKits(const int kits[], int size)
{
    int runningKitTotal = 0;

    for(int i = 0; i < size; i++)
    {
        runningKitTotal += kits[i];
    }

    return runningKitTotal;
}


int main()
{
    int kitCount[4];
    kitCount[0] = 8;
    kitCount[1] = 12;
    kitCount[2] = 6;
    kitCount[3] = 10;
    int startingTotal;
    int extraAmount;
    int endingTotal;

    startingTotal = calculateTotalKits(kitCount, 4);

    cout << "Starting total is " << startingTotal << "\n";
    cout << "Please enter extra amount (0 - 10) kits per hub " << "\n";
    cin >> extraAmount;

    addReserveKits(kitCount, 4, extraAmount);

    for(int i = 0; i < 4; i++)
    {
        cout << "Array at spot " << i << " has " << kitCount[i];
    }

    endingTotal = calculateTotalKits(kitCount, 4);

    cout <<"Ending total is " << endingTotal;

    return 0;
}