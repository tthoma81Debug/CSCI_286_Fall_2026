#include <iostream>

using namespace std;

int main()
{
    int litersBeingAdded;
    int totalAmount = 0;

    do
    {
        cout << "How many liters are being added? \n";
        cin >> litersBeingAdded;

        totalAmount += litersBeingAdded;
    }
    while(totalAmount <= 50);



    return 0;
}
