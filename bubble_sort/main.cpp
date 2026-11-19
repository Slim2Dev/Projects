#include <iostream>
using namespace std;

void printArray(int tab[])
{
    for(int i=0; i<6; i++)
    {
        cout << " " << tab[i] << ", ";
    }
}

int main()
{

    int tab[6] = {9,7,2,5,11,4};
    int temp = 0;
    bool swapped = true;

    cout << "\n";
    printArray(tab);

    while(swapped==true)
    {
        swapped = false;
        for(int i=0; i<5; i++)
        {
            if(tab[i]>tab[i+1])
            {
                temp = tab[i];
                tab[i] = tab[i+1];
                tab[i+1] = temp;
                swapped = true;
            }
        }
    }

    cout << "\n";
    printArray(tab);

    return 0;

}