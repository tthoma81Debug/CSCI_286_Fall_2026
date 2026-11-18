#include <iostream>

using namespace std;



int main()
{
    int integerArray[5];
    int totalParticipants = 0;
    int totalWorkshopsWith25OrMore = 0;
    double average;

    for(int i = 0; i < 5; i++)
    {
        do
        {
            cout << "Please enter total number of workshop participants (0 through 40) \n";
            cin >> integerArray[i];
        } 
        while (integerArray[i] > 40 || integerArray[i] < 0);
        
    }//values are now all stored


    //prints array and calculates total
    for(int i = 0; i < 5; i++)
    {
        totalParticipants += integerArray[i];

        if(integerArray[i] >= 25)
        {
            totalWorkshopsWith25OrMore++;
        }

        cout << integerArray[i] << "\n"; //outputs contents of array.
    }
    cout << "Total Participants: " << totalParticipants << "\n";
    cout << "Total Workshops 25 or More: " << totalWorkshopsWith25OrMore << "\n";

    //calculate average per workshop.
    average = totalParticipants / 5.0;
    cout << "Average is " << average << "\n";


    return 0;
}
