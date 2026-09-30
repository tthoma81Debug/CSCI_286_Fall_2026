#include <iostream>

using namespace std;

int main()
{
    int countdownNumber;

    cout << "Starting countdown number please \n";
    cin >> countdownNumber;

    if(countdownNumber >= 1)
    {
        //accept starting value
        while(countdownNumber >= 1)
        {
            cout << countdownNumber << "\n";

            countdownNumber--;
        }

        cout << "Field Station Now Open \n";

    }
    else
    {
        //reject starting value
        cout << "that number is less than 1. rejected \n"; 
    }

    
    return 0;
}
