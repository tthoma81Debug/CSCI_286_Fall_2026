#include <iostream>

using namespace std;

char getLoadCategory(int kits)
{
    char category;
    if(kits >= 30)
    {
        //category is A
        category = 'A';
    }
    else if(kits >= 15 && kits <= 29)
    {
        //category is B
        category = 'B';
    }
    else if(kits < 15)
    {
        //category is C
        category = 'C';
    }
    else
    {
        //should never happen
        cout <<"oops. this error shouldn't display. talk to support";
    }

    return category;
}


int main()
{
    int kitCount;
    cout << "please enter a kitcount (0 through 100) \n";
    cin >> kitCount;

    return 0;
}