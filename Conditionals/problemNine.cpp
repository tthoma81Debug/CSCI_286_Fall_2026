#include <iostream>
#include <ctime>

using namespace std;

int main()
{
    srand(time(nullptr));

    int raw_random;
    int random_one;
    
    raw_random = rand();
    random_one = raw_random % 10;

    cout <<"The raw_random number we generated is " << raw_random << "\n";
    cout <<"The random_one number we generated is " << random_one << "\n";

    return 0;
}
