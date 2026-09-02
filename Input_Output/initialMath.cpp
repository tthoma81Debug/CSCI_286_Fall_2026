#include "greeting.h"
#include <iostream>

using namespace std;

int main()
{
    int numToDeploy;
    int extraCountermeasures = 3;
    int totalDeployed = 999999;
    int incomingAntiSat = 5;
    float countermeasureEffectiveness = 0.7352f;
    double antiSatCountermeasureAvoidanceRating = 0.523;
    float antiSatIntercepted;
    float totalIntercepted;
    cout << "How many satellites would you like to deploy?";
    cin >> numToDeploy;


    //assume the user needs a few more for countermeasures
    //numToDeploy = numToDeploy + 3;
    //numToDeploy += 3;
    //numToDeploy += extraCountermeasures;

    //extraCountermeasures = extraCountermeasures + 1;
    extraCountermeasures++;

    

    totalDeployed = numToDeploy + extraCountermeasures;

    totalIntercepted = extraCountermeasures * countermeasureEffectiveness;

    antiSatIntercepted = incomingAntiSat - totalIntercepted;
 
    cout << "Roger that. Deploying " << numToDeploy << " satellites \n";
    cout << "Auto deploying " << extraCountermeasures << " to protect from anti satellite weaponry \n";
    cout << "Total deployed: " << totalDeployed;

    cout << "\n Incoming Anti Sat! " << incomingAntiSat << " projectiles!. Engaging with " << extraCountermeasures << " countermeasures \n"; 
    cout << "We have capacity to intercept " << totalIntercepted << "\n";
    cout <<"Interception! " << antiSatIntercepted << " anti sat projectiles intercepted \n";




    return 0;
}
