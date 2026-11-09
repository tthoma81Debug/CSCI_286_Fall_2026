#include <iostream>
#include <fstream>
using namespace std;

int main() {
   
    int batteryCharge[5];

    for(int i = 0; i < 5; i++)
    {
        cout <<"Please enter next battery percentage for battery " << i << " \n";
        cin >> batteryCharge[i];
    }
    

    return 0;
}
