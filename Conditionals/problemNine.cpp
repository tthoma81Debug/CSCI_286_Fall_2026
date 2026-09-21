#include <iostream>
#include <ctime>

using namespace std;

int main()
{
    srand(time(nullptr));
    
    /*
    int raw_random;
    int random_one;
    int final_random; //number in range 1 to 10
    
    raw_random = rand();
    random_one = raw_random % 10;
    final_random = random_one + 1;

    cout <<"The raw_random number we generated is " << raw_random << "\n";
    cout <<"The random_one number we generated is " << random_one << "\n";
    cout <<"The final_random number we generated is " << final_random << "\n";

    */
    string outputString;
    int random_number = (rand() % 51) - 10; //will give 0 - 50 and then becomes -10 through 40
    //int rand_step_2 = initial_rand + 1; //will give 1 - 40

    cout <<"random number is " << random_number << "\n";

    if(random_number < 0)
    {
        outputString = "Below Freezing";
    }
    else if(random_number >= 0 && random_number <= 15)
    {
        outputString = "Cold";
    }
    else if(random_number > 15 && random_number <= 30)
    {
        outputString = "Mild";
    }
    else if(random_number > 30)
    {
        outputString = "Hot";
    }
    else
    {
        outputString = "this should never happen. if you see it. something went wrong";
    }
    cout << outputString;


    return 0;
}
