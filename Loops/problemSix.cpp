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

        if(litersBeingAdded <= 0)
        {
            cout << "You are adding a negative amount of water...not counting...try again \n";
        }
        else
        {
            totalAmount += litersBeingAdded;
            cout <<"Thanks! Running total is now " << totalAmount << "\n";
        }

       
    }
    while(totalAmount <= 50);

    cout << "Tank is ready! \n";

    return 0;
}
