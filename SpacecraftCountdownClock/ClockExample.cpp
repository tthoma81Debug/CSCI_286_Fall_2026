#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    int userSuppliedTotalSeconds;
    int minutes;
    int hours;
    int leftoverSeconds;
    int leftoverMinutes;
    string minutesString;
    string secondsString;
    string outputString;
    string hoursString;

    cout << "Please enter the countdown timer amount in seconds. \n";
    cin >> userSuppliedTotalSeconds;

    minutes = userSuppliedTotalSeconds / 60;
    hours = (userSuppliedTotalSeconds / 60) / 60;
    leftoverMinutes = (minutes % 60);
    leftoverSeconds = userSuppliedTotalSeconds % 60;

    hoursString = to_string(hours);
    minutesString = to_string(leftoverMinutes);
    secondsString = to_string(leftoverSeconds);

    hoursString  += " Hours Remaining. ";
    minutesString += " Minutes Remaining. ";
    secondsString += " Seconds Remaining";

    outputString = hoursString + minutesString + secondsString;

    cout << outputString;

    //cout << endl;
    //cout << "\n";

    double numberToSquare = 100;
    double numberToRaise = 3.2;
    double cubedNumber = pow(3, 2);
    double squareRootNumber = sqrt(numberToSquare);
    double raisedNumber = ceil(numberToRaise);
    cout << " \n";
    cout << cubedNumber;
    cout << " and square root number is " << squareRootNumber;
    cout << " and raised number is " << raisedNumber;

    return 0;
}
