#include "greeting.h"
#include <iostream>

using namespace std;

int Notmain()
{

    string first_name; //the first name of the user
    string last_name;
    string full_name; //the full name of the user
    int age;
    cout << "This is cool";
    cout << " and this is another set of words to print \n";
    cout << "Hello, what is your first name? \n";

    cin >> first_name;

    cout << "That's neat. Your firstname is " + first_name + " but what is your last name? \n";

    cin >> last_name;

    full_name = first_name + " " + last_name;

    //commented out for upgraded version
    //cout << "That is cool I guess. I'll remember that your first name is " << first_name << " and your last name is " + last_name;

    cout << "That's cool. I will remember your name is " + full_name + "\n";

    cout << "What is your age? \n";

    cin >> age;

    cout << "my apologies... your age is ";
    cout << age;


    /******
    int fifteen = 15;
    int five = 5;
    int sum = fifteen + five;
    cout << sum;
    *******/


    return 0;
}
