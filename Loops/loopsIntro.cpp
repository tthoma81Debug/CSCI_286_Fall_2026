#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    int counter = 0;

    while(counter < 100)
    {
        cout << "Counter is \t" << counter << " and the square of it is " << pow(counter, 2) << "\n";
        counter++;
    }

    return 0;
}
