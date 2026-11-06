#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ofstream output("mission_sign.txt");

    if (!output) {
        cout << "Could not open mission_sign.txt\n";
        return 1;
    }

    output << "BLUE RIDGE SKYWATCH\n";
    output << "Operation Lantern\n";
    output << "Serving our neighbors under the stars\n";

    output.close();

    cout << "Mission sign saved.\n";
    return 0;
}
