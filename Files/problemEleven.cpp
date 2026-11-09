#include <iostream>
#include <fstream>
#include <string>
using namespace std;

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
    }


    input.close();

    return 0;
}
