#include <iostream>

using namespace std;

int main()
{
    int userSuppliedTotalSeconds;
    int minutes;
    int hours;
    int leftoverSeconds;
    string minutesString;
    string secondsString;
    string outputString;
    string hoursString;

    cout << "Please enter the countdown timer amount in seconds. \n";
    cin >> userSuppliedTotalSeconds;

    minutes = userSuppliedTotalSeconds / 60;
    hours = (userSuppliedTotalSeconds / 60) / 60;
    leftoverSeconds = userSuppliedTotalSeconds % 60;

    hoursString = to_string(hours);
    minutesString = to_string(minutes);
    secondsString = to_string(leftoverSeconds);

    minutesString += " Minutes Remaining. ";
    secondsString += " Seconds Remaining";

    outputString = minutesString + secondsString;

    cout << outputString;

    //cout << endl;
    cout << "\n";

    cout << "hours is " + hoursString;

    return 0;
}
