#include <iostream>
#include <fstream>
using namespace std;

int main() {
   
    int batteryCharge[5];
    int tempUserEntry;

    for(int i = 0; i < 5; i++)
    {
        do
        {
            cout <<"Please enter next battery percentage for battery " << i << " \n";
            cin >> tempUserEntry; 
        }
        while(tempUserEntry < 0 || tempUserEntry > 100);

        //if here, then the percentage for THIS slot is corect.
        //save into array.
        batteryCharge[i] = tempUserEntry;
        
    } //end for loop

    //array is ready. now write to file.
    ofstream output("battery_capture.txt");

    for(int i = 0; i < 5; i++)
    {
        output << batteryCharge[i] << "\n";
    }

    output.close();
    cout << "File Created \n";



    

    return 0;
}
