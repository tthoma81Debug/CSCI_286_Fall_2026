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
        category = 'F';
    }

    return category;
}


int main()
{
    int kitCount;
    char category;
    cout << "please enter a kitcount (0 through 100) \n";
    cin >> kitCount;

    category = getLoadCategory(kitCount);
    cout << "category is: " << category << "\n";

    if(category == 'A')
    {
        cout << "Large Practice Load \n";
    }
    else if(category == 'B')
    {
        cout << "Medium Practice Load \n";
    }
    else if(category == 'C')
    {
        cout << " Small Practice Load \n";
    }
    else
    {
        cout << "oops. there was an error. not gonna try to guess what. \n";
    }


    return 0;
}