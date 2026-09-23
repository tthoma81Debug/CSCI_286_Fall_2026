#include <iostream>
#include <ctime>
#include <cmath>

using namespace std;

int main()
{
    int a_variable;
    int b_variable;
    int c_variable;
    int discriminant;

    cout <<"Enter the valu of 'a'in the quadratic equation \n";
    cin >> a_variable;
    cout <<"Enter the valu of 'b'in the quadratic equation \n";
    cin >> b_variable;
    cout <<"Enter the valu of 'c'in the quadratic equation \n";
    cin >> c_variable;

    cout <<"test" << b_variable << " " << c_variable;

    discriminant = pow(b_variable, 2) - (4 * a_variable * c_variable);

    if(a_variable == 0)
    {
        //treat the whole thing as linear equation
        
        if(a_variable == 0 && b_variable == 0)
        {
            if(c_variable == 0)
            {
                //every number is a solution
            }
            else
            {
                //there is no solution
            }
        }

    }


    if(discriminant > 0)
    {
        //calculate and print both real solutions
        double x1 = (-b_variable + sqrt(discriminant)) / (2 * a_variable);
        double x2 = (-b_variable - sqrt(discriminant)) / (2 * a_variable);
        cout << "Two real solutions\n";
        cout << "x1 = " << x1 << '\n';
        cout << "x2 = " << x2 << '\n';


    }
    else if(discriminant == 0)
    {
        //calculate and print the one real solution
    }
    else if (discriminant < 0)
    {
        //print no real solutions.
        cout << "No real solutions \n";
    }
    else
    {
        cout << "Error. should never be logically possible. in Else block";
    }


    return 0;
}
