#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//pass 1 for charged battery. 0 for low battery
void batteryStatusWrite(int batteryType, int batteryCharge)
{
    string fileToWrite;

    if(batteryType == 1)
    {
        fileToWrite = "ready_batteries.txt";
    }
    else
    {
        fileToWrite = "low_batteries.txt";
    }

    ofstream output(fileToWrite, ios::app);
        if (!output) {
        cout << "Could not open file for writing. error.\n";
    }

    output << batteryCharge << "\n";

    output.close();


}

int main() {

    ifstream input("battery_scan.txt");
    string lineFromBatteryScan;

    int amountLowBatteries = 0;
    int amountReadyBatteries = 0;
    int amountInvalidBatteries = 0;

    //check to make sure we actually found the file.
    if (!input) {
        cout << "Could not open battery_scan.txt\n";
        return 1;
    }

    //if we get this far... then lets read the first line
    while (getline(input, lineFromBatteryScan)) {
        cout << lineFromBatteryScan << '\n';
        int convertedBatteryScanLine;
        convertedBatteryScanLine = stoi(lineFromBatteryScan);

        if(convertedBatteryScanLine > 100 || convertedBatteryScanLine < 0)
        {
            cout << "Invalid battery charge. not writing to file \n";
            amountInvalidBatteries++;
            continue;
        }
        else
        {
            cout << "This item is valid \n";

            if(convertedBatteryScanLine >= 60 && convertedBatteryScanLine <= 100)
            {
                //goes to charged battery file
                batteryStatusWrite(1, convertedBatteryScanLine);
                amountReadyBatteries++;
            }
            else if (convertedBatteryScanLine < 60 && convertedBatteryScanLine >= 0)
            {
                //goes to low battery file
                batteryStatusWrite(0, convertedBatteryScanLine);
                amountLowBatteries++;
            }
            else
            {
                //should never happen
                cout <<"oops. invalid battery slipped through somehow \n";
                return 1;
            }
        }




    } //end loop

    cout << amountReadyBatteries << " batteries ready \n";
    cout << amountLowBatteries << " low batteries \n";
    cout << amountInvalidBatteries << " messed up batteries \n";

    input.close();

    return 0;
}
