#include <iostream>
#include "BeaconMath.h"

double estimateRuntime(double wattHours, double watts)
{
    double runtimeEstimate;
    runtimeEstimate = wattHours / watts;
    return runtimeEstimate;;
}

double calculateEnergyNeeded(double watts, double hours)
{
    return watts * hours;
}