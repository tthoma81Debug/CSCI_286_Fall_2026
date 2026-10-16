#include <iostream>


using namespace std;

int main()
{
    double challengeTimes[8];
    double currentLowest;
    int lowestScoreTeamNumber;

    for(int i = 0; i < 8; i++)
    {
        cout <<"Please enter a time in minutes for challenger " << (i + 1) << "\n";
        cin >> challengeTimes[i];
    }

    //find lowest challenge time
    //assume first we see is lowest
    currentLowest = challengeTimes[0];
    lowestScoreTeamNumber = 0;


    for(int i =1; i < 8; i++)
    {
        if(currentLowest > challengeTimes[i])
        {
            currentLowest = challengeTimes[i];
            lowestScoreTeamNumber = i;
        }
    }

    







    //now we have the lowest
    cout <<"Lowest Challenge Time: " << currentLowest << "\n";
    cout <<"And that score is from team " << (lowestScoreTeamNumber + 1) << "\n";









    //find lowest challenge time

    //calculate average challenge time

    //find highest psuedocode
    //assume the first one is the highest
    // compare to second, third fourth etc
    // when comparing, if what you are looking at is larger than the largest seen so far, it becomes the largest seen so far
    // when you search the whole array, you have the largest number set aside.




    return 0;
}
