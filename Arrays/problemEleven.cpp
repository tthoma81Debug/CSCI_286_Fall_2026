#include <iostream>


using namespace std;

int main()
{
    double challengeTimes[8];
    double currentLowest;
    double currentHighest;
    int lowestScoreTeamNumber;
    int highestScoreTeamNumber;
    int scoreSum = 0;
    double average;

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

    //find highest challenge time
    //assume first we see is highest
    currentHighest = challengeTimes[0];
    highestScoreTeamNumber = 0;


    for(int i =1; i < 8; i++)
    {
        if(currentHighest < challengeTimes[i])
        {
            currentHighest = challengeTimes[i];
            highestScoreTeamNumber = i;
        }
    }


    //average = all values added up / total number of values

    for(int i = 0; i < 8; i++)
    {
        scoreSum += challengeTimes[i];
    }

    average = scoreSum / 8.0;



    //now we have the lowest
    cout <<"Lowest Challenge Time: " << currentLowest << "\n";
    cout <<"And that score is from team " << (lowestScoreTeamNumber + 1) << "\n";

    //and highest
    cout <<"Highest Challenge Time: " << currentHighest << "\n";
    cout <<"And that score is from team " << (highestScoreTeamNumber + 1) << "\n";

    //and average
    cout <<"Average Challenge Time: " << average << "\n";







    //find lowest challenge time

    //calculate average challenge time

    //find highest psuedocode
    //assume the first one is the highest
    // compare to second, third fourth etc
    // when comparing, if what you are looking at is larger than the largest seen so far, it becomes the largest seen so far
    // when you search the whole array, you have the largest number set aside.




    return 0;
}
