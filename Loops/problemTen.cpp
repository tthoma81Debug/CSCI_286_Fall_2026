#include <iostream>

using namespace std;

int main()
{
    int samplesToGenerate;

    cout << "How many samples should be generated \n";
    cin >> samplesToGenerate;

    if(samplesToGenerate >= 1 && samplesToGenerate <=20)
    {
       //can proceed

       //for loops would look like
       for(int i = 0; i < 20; i++) //will change
       {
        //change for loop logic
       }


    }
    else
    {
        cout <<"samples to generate not between 1 and 20 \n";
    }


    return 0;
}
