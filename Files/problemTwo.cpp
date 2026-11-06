#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    ifstream input("welcome.txt");

    if (!input) {
        cout << "Could not open welcome.txt\n";
        return 1;
    }

    string message;

    if (getline(input, message)) {
        cout << message << '\n';
    } else {
        cout << "The welcome file is empty.\n";
    }

    input.close();
    return 0;
}
