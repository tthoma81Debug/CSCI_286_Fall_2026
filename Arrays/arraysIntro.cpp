#include <iostream>


using namespace std;

int main()
{
    // 1. Modern C++ syntax (Recommended)
    int arr1[]{10, 20, 30, 40, 50};

    // 2. Traditional syntax with implicit size
    int arr2[] = {10, 20, 30, 40, 50};

    // 3. Traditional syntax with explicit size
    int arr3[5] = {10, 20, 30, 40, 50};

    //array declaration. no initialization. MUST have array size.
    int myArrayCustom[5];

    //bad practice. if initialize. do all values.
    //int myArrayCustomTwo[5] = {10, 20, 40, 50};


    myArrayCustom[0] = 50;
    myArrayCustom[1] = 150;
    myArrayCustom[2] = 20;
    myArrayCustom[3] = 50;
    myArrayCustom[4] = 900;

    for(int i = 0; i < 5; i++)
    {
        myArrayCustom[i]++;
    }


    return 0;
}
