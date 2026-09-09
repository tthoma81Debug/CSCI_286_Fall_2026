#include <iostream>

using namespace std;

int main()
{
    int userSuppliedTotalSeconds;
    int minutes;
    string minutesString;

    cout << "Please enter the countdown timer amount in seconds. \n";
    cin >> userSuppliedTotalSeconds;

    minutes = userSuppliedTotalSeconds / 60;

    minutesString = to_string(minutes);
    minutesString += " Minutes Remaining";
    //minutesString = minutes;
    // + " Minutes Total";
    


    cout << minutesString;

    return 0;
}
