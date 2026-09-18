#include <iostream>

using namespace std;

int main()
{
    double gardenTemp;
    double storageTemp;

    cout << "Please enter garden temperature sensor reading \n";
    cin >> gardenTemp;

    cout << "Please enter storage temperature sensor reading \n";
    cin >> storageTemp;

    if(gardenTemp > storageTemp)
    {
        cout << "Sensor 1 recorded the higher temperature \n";
    }

    return 0;
}
