#include <iostream>
#include <ctime>

using namespace std;

int main()
{
    int samplesToGenerate;
    int raw_random;
    int random_one;

    int totalAcids = 0;
    int totalNeutrals = 0;
    int totalBases = 0;

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
            cout << random_one << "\n";

            if(random_one < 7)
            {
                //then it is acid....like heartburn
                totalAcids++;
            }
            else if (random_one == 7)
            {
                //then it is neutral
                totalNeutrals++;
            }
            else if (random_one > 7)
            {
                //basic as oven cleaner
                totalBases++;
            }
            else
            {
                //should never happen
                cout <<"uh oh. in else block";
            }


       }


    }
    else
    {
        cout <<"samples to generate not between 1 and 20 \n";
    }


    return 0;
}
