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

    ofstream output(fileToWrite);
        if (!output) {
        cout << "Could not open file for writing. error.\n";
    }

    output << batteryCharge << "\n";

    output.close();


}

int main() {

    ifstream input("battery_scan.txt");
    string lineFromBatteryScan;

    //check to make sure we actually found the file.
    if (!input) {
        cout << "Could not open battery_scan.txt\n";
        return 1;
    }

    //if we get this far... then lets read the first line
    if (getline(input, lineFromBatteryScan)) {
        cout << lineFromBatteryScan << '\n';
        int convertedBatteryScanLine;
        convertedBatteryScanLine = stoi(lineFromBatteryScan);

        if(convertedBatteryScanLine > 100 || convertedBatteryScanLine < 0)
        {
            cout << "Invalid battery charge. not writing to file \n";
            return 1;
        }
        else
        {
            cout << "This item is valid \n";

            if(convertedBatteryScanLine >= 60 && convertedBatteryScanLine <= 100)
            {
                //goes to charged battery file
                batteryStatusWrite(1, convertedBatteryScanLine);
            }
            else if (convertedBatteryScanLine < 60 && convertedBatteryScanLine >= 0)
            {
                //goes to low battery file
                batteryStatusWrite(0, convertedBatteryScanLine);
            }
            else
            {
                //should never happen
                cout <<"oops. invalid battery slipped through somehow \n";
                return 1;
            }
        }




    }




    input.close();

    return 0;
}
