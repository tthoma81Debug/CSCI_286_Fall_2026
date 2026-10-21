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

   

    return 0;
}

