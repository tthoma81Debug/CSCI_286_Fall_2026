#include <iostream>
#include "problem15Math.h"

using namespace std;



int main()
{
    double storedEnergy;
    double powerDraw;
    double runtime;

    cout << "Please enter stored energy (0 through 1000 watt hours) \n";
    cin >> storedEnergy;

    cout <<" Please enter a power draw (0 to 1000 watts) \n";
    cin >> powerDraw;

    runtime = estimateRuntime(storedEnergy, powerDraw);

    cout << "runtime is " << runtime << "\n";

    if(runtime >= 6)
    {
      cout << "runtime target met \n";
    }
    else
    {
        cout <<"runtime target not met \n";
    }

    return 0;
}

double estimateRuntime(double wattHours, double watts)
{
    return wattHours / watts;
}