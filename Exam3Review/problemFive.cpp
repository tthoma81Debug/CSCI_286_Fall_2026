#include <iostream>

using namespace std;

int previewExtra(int count);
bool checkOut(int& count, int requested);

int previewExtra(int count)
{
    return (count + 5);
}

bool checkOut(int& count, int requested)
{
    bool success = false;
    if(requested <= count)
    {
        count -= requested;
        success = true;
    }
    else
    {
        success = false;
    }

    return success;
}


int main()
{
    int startingCount;
    int finalCount;
    int valueFromPreviewExtra;
    int requested;
    bool checkoutSuccess = false;

    cout << "Enter a starting count \n";
    cin >> startingCount;

    valueFromPreviewExtra = previewExtra(startingCount);

    cout <<"original count " << startingCount << "\n";
    cout << "count with preview included " << valueFromPreviewExtra << "\n";

    cout <<"Enter amount to check out \n";
    cin >> requested;
    checkoutSuccess = checkOut(startingCount, requested);
    finalCount = startingCount;

    if(checkoutSuccess == true)
    {
        cout <<"Checkout Success: total remaining " << finalCount << "\n";
    }
    else
    {
        cout <<"Checkout failed. was the amount requested valid? \n";
    }



    return 0;
}
