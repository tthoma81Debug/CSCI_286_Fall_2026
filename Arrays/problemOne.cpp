#include <iostream>


using namespace std;

int main()
{
    int welcomeHeadcount[5];

    for(int i = 0; i < 5; i++)
    {
        cout << "How many visitors did desk " << i << " help \n";
        cin >> welcomeHeadcount[i];    
    }

    //output
    for(int i = 0; i < 5; i++)
    {
        cout << "desk " << (i + 1) << " helped " << welcomeHeadcount[i] << " people \n";
    }

    return 0;
}
