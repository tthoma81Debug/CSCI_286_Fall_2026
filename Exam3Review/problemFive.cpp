#include <iostream>

using namespace std;

int previewExtra(int count);
bool checkOut(int& count, int requested);

int previewExtra(int count)
{
    return (count + 5);
}


int main()
{
    int startingCount;
    int valueFromPreviewExtra;
    int requested;

    cout << "Enter a starting count \n";
    cin >> startingCount;

    valueFromPreviewExtra = previewExtra(startingCount);

    cout <<"original count " << startingCount << "\n";
    cout << "count with preview included " << valueFromPreviewExtra << "\n";

    cout <<"Enter amount to check out \n";
    cin >> requested;


    return 0;
}
