#include <iostream>


using namespace std;

int main()
{
    int claimCodes[12];

    for(int i =0; i < 12; i++)
    {
        cout <<"Please enter the claim code for item " << (i+1);
        cin >> claimCodes[i];
    }

    return 0;
}
