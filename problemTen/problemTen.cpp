#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main()
{
    float floatAltitude = 250000.0f;
    double doubleAltitude = 250000.0;

    float floatAltitudeCopy = 250000.0f;
    double doubleAltitudeCopy = 250000.0;

    floatAltitude += 0.2;
    floatAltitude += 0.2;
    floatAltitude += 0.2;
    floatAltitude += 0.2;
    floatAltitude += 0.2;

    doubleAltitude += 0.2;
    doubleAltitude += 0.2;
    doubleAltitude += 0.2;
    doubleAltitude += 0.2;
    doubleAltitude += 0.2;

    float changeFloat = floatAltitude - floatAltitudeCopy;
    double changeDouble = doubleAltitude - doubleAltitudeCopy;

    cout << fixed << setprecision(20);

    cout << "Starting Float Value " << floatAltitudeCopy << "\n";
    cout << "Final Float Value " << floatAltitude << "\n";
    cout << "Starting Double Value " << doubleAltitudeCopy << "\n";
    cout << "Final Double Value " << doubleAltitude << "\n";
    cout << "Change measured by the float" << changeFloat << "\n";
    cout << "Change measured by the double" << changeDouble << "\n";
    cout << "Expected Change " << "1.0" << "\n";



    return 0;
}
