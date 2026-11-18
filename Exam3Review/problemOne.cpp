#include <iostream>

using namespace std;



int main()
{
    int integerArray[5];
    int workshopParticipants;
    for(int i = 0; i < 5; i++)
    {
        do
        {
            cout << "Please enter total number of workshop participants (0 through 40) \n";
            cin >> integerArray[i];
        } 
        while (integerArray[i] > 40 || integerArray[i] < 0);
        

    }

    return 0;
}
