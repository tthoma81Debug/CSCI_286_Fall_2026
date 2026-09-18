#include <iostream>

using namespace std;

int main()
{
    double completedServiceHours;
    string sayThisString = "Starting Value";

    cout << "Please enter the amount of completed service hours \n";
    cin >> completedServiceHours;

    if (completedServiceHours > 5)
    {
        sayThisString = "Eligible for the service team";
    }
    else if(completedServiceHours < 0) 
    {
        sayThisString = "Hang on...you worked negative hours? how is this this possible?.";
    }
    else
    {
         sayThisString = "More service hours needed";//logic here
    }
    

    cout << sayThisString;


    return 0;
}
