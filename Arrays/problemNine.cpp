#include <iostream>


using namespace std;

int main()
{
    int claimCodes[12];
    int codeSearchingFor;
    bool searchSuccess = false;

    for(int i =0; i < 12; i++)
    {
        cout <<"Please enter the claim code for item " << (i+1);
        cin >> claimCodes[i];
    }

    //linear search
    cout << "Please enter the claim code of the item you are looking for \n";
    cin >> codeSearchingFor;

    if(codeSearchingFor == claimCodes[0])
    {
        cout << "Claim Code Found! At location " << (0 + 1);
        searchSuccess = true;
    }
    else
    {
        //code at this spot doesn't match.
    }

    if(searchSuccess == true)
    {
        //great! already output result so all set

    }
    else
    {
        //checked array. item not there
        cout << "Claim Code Not Found \n";
    }




    return 0;
}
