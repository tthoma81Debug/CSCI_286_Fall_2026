#include <iostream>


using namespace std;

int main()
{
    int claimCodes[12];
    int codeSearchingFor;
    bool searchSuccess = false;

    for(int i =0; i < 12; i++)
    {
        cout <<"Please enter the claim code for item " << (i+1) <<"\n";
        cin >> claimCodes[i];
    }

    //linear search
    cout << "Please enter the claim code of the item you are looking for \n";
    cin >> codeSearchingFor;

    for(int i = 0; i < 12; i++)
    {

    if(codeSearchingFor == claimCodes[i])
    {
        cout << "Claim Code Found! At location " << (i + 1);
        searchSuccess = true;
        break;
    }
    else
    {
        //code at this spot doesn't match.
    }

    } //end loop

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
