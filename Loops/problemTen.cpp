#include <iostream>
#include <ctime>

using namespace std;

int main()
{
    int samplesToGenerate;
    int raw_random;
    int random_one;

    srand(time(nullptr));

    cout << "How many samples should be generated \n";
    cin >> samplesToGenerate;

    if(samplesToGenerate >= 1 && samplesToGenerate <=20)
    {
       //can proceed

       //for loops would look like
       for(int i = 0; i < samplesToGenerate; i++) //will change
       {
            //change for loop logic
            raw_random = rand();
            random_one = raw_random % 15;
       }


    }
    else
    {
        cout <<"samples to generate not between 1 and 20 \n";
    }


    return 0;
}
