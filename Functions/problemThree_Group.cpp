#include <iostream>

using namespace std;


int calculatePacks(int teams, int packsPerTeam)
{
    return teams * packsPerTeam;
}

int main()
{
    int numberTeams;
    int packsPerTeam;
    int requiredPacks;
    int secondTotal;

    cout << "Plese enter number of teams, from 1 through 20. \n";
    cin >> numberTeams;
    cout << "Please enter packs per team, from 1 through 50. \n";
    cin >> packsPerTeam;

    requiredPacks = calculatePacks(numberTeams, packsPerTeam);

    secondTotal = requiredPacks + 5;

    cout <<"required packs (first total): " << requiredPacks << "\n";
    cout <<"packs with spare included (second total): " << secondTotal << "\n";

    return 0;
}