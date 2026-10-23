#include <iostream>

using namespace std;

double calculateKitCost(int kitCountTotal, double kitPrice)
{
    double kitTotalCost;

    kitTotalCost = kitCountTotal * kitPrice;

    return kitTotalCost;
}

int main()
{
    int kitCount;
    double kitPrice;
    double subtotal;
    double deliveryCharge = 12.0;
    double total;

    cout <<"Please enter a kit count (0 through 100) \n";
    cin >> kitCount;   
    cout <<"Please enter a price per kit ($0 through $25) \n";
    cin >> kitPrice;

    subtotal = calculateKitCost(kitCount, kitPrice);
    total = subtotal + deliveryCharge;

    cout << "Subtotal: " << subtotal << "\n";
    cout << "Total: " << total << "\n";


    return 0;
}