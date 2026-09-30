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
        }

       
    }
    while(totalAmount <= 50);



    return 0;
}
