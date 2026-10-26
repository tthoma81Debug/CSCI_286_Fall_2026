#include <iostream>
#include "BeaconMath.h"

using namespace std;


int main()
{
    double watts;
    double storedEnergy;
    double runtime;
    cout << "Please enter stored energy. 0 through 1000 watt hours \n";
    cin >> storedEnergy;

    cout << "Power draw? 0 through 1000 watts \n";
    cin >> watts;

    runtime = estimateRuntime(storedEnergy, watts);

    cout <<"runtime is " << runtime << "\n";

    if(runtime >= 6)
    {
        cout <<"Runtime Target Achieved\n";
    }
    else
    {
        cout <<"Runtime Target Failed \n";
    }

    return 0;
}

double estimateRuntime(double wattHours, double watts)
{
    double runtimeEstimate;
    runtimeEstimate = wattHours / watts;
    return runtimeEstimate;;
}