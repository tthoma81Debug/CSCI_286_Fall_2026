#include "greeting.h"
#include <iostream>

using namespace std;

int main()
{
    int numToDeploy;
    int extraCountermeasures = 3;
    int totalDeployed = 999999;
    float countermeasureEffectiveness = 0.7352;
    cout << "How many satellites would you like to deploy?";
    cin >> numToDeploy;


    //assume the user needs a few more for countermeasures
    //numToDeploy = numToDeploy + 3;
    //numToDeploy += 3;
    //numToDeploy += extraCountermeasures;

    //extraCountermeasures = extraCountermeasures + 1;
    extraCountermeasures++;


    totalDeployed = numToDeploy + extraCountermeasures;

    cout << "Roger that. Deploying " << numToDeploy << " satellites \n";
    cout << "Auto deploying " << extraCountermeasures << " to protect from anti satellite weaponry \n";
    cout << "Total deployed: " << totalDeployed;
    cout << "And this was added to show Github Working";
    return 0;
}
