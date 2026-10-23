#include <iostream>

using namespace std;

int getDailyGoal()
{
    return 24;
}

int main()
{
    int goal = 0;
    int stillNeeded;
    int completedGoals;
    goal = getDailyGoal();

    cout << "How many kits have already been completed (0 - 24)\n";
    cin >> completedGoals;

    stillNeeded = goal - completedGoals;

    cout << "the goal is " << goal << "\n";
    cout << stillNeeded << " kits still needed";

   

    return 0;
}

