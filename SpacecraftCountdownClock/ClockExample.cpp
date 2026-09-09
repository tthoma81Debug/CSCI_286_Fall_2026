#include <iostream>

using namespace std;

int main()
{
    int userSuppliedTotalSeconds;
    int minutes;
    int leftoverSeconds;
    string minutesString;
    string secondsString;
    string outputString;

    cout << "Please enter the countdown timer amount in seconds. \n";
    cin >> userSuppliedTotalSeconds;

    minutes = userSuppliedTotalSeconds / 60;
    leftoverSeconds = userSuppliedTotalSeconds % 60;

    minutesString = to_string(minutes);
    secondsString = to_string(leftoverSeconds);

    minutesString += " Minutes Remaining. ";
    secondsString += " Seconds Remaining";

    outputString = minutesString + secondsString;

    cout << outputString;

    return 0;
}
