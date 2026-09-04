#include "greeting.h"
#include <iostream>

using namespace std;

int main()
{
    //lets find out how many square feet are needed for a floor plan
    //user will supply length and width;

    float length = 0;
    float width = 0;
    float area;
    float perimeter;
    int numberToDivide = 8;
    int answer;

    //bool hasPurchased = true;
    //cout << "have you purchased flooring yet? Enter 1 for yes, and 0 for no \n";
    //cin >> answer;

    int totalFloorTilesPurchased = 100;
    int totalFloorTilesAvailable = 800;

    int totalAvailableTilesUsed = totalFloorTilesPurchased / totalFloorTilesAvailable;

    cout << "total available tiles uses (as percent): " << totalAvailableTilesUsed; //note that this is actually 0 because it is integer division.


    cout << "Lets find out how many square feet of flooring you need. How long is the room? \n";
    cin >> length;

    cout <<"how wide is the room? \n";
    cin >> width;

    area = length * width;
    perimeter = 2 * length + 2 * width;

    cout << "you need a total of " << area << " square feet of flooring \n";
    cout << "Also, the perimeter is " << perimeter << " feet";

    answer = numberToDivide / 2;


    return 0;
}
