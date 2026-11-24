#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

void generateBoard(char _gameboard[20][20])
{
    for(int i=0; i<20; i++)
    {
        for(int j=0; j<20; j++)
        {
            _gameboard[i][j] = '.';
            cout << setw(3) << _gameboard[i][j];
        }
        cout << "\n";
    }
    cout << "\n";
}

void printCurrentBoard(char _gameboard[20][20])
{
    for(int i=0; i<20; i++)
    {
        for(int j=0; j<20; j++)
        {
            cout << setw(3) << _gameboard[i][j];
        }
        cout << "\n";
    }
    cout << "\n";
}

bool checkIfBoardHasEmptySpace(char _gameboard[20][20])
{
    for(int i=0; i<20; i++)
    {
        for(int j=0; j<20; j++)
        {
            if(_gameboard[i][j]=='.')
            {
                return true;
            }
        }
    }
    return false;
}

void randGenerateApple(char _gameboard[20][20])
{
    while(checkIfBoardHasEmptySpace(_gameboard))
    {
        int rand_x = rand() % 20;
        int rand_y = rand() % 20;
        if(_gameboard[rand_x][rand_y] == '.')
        {
            _gameboard[rand_x][rand_y] = 'A';
            break;
        }
    }
}

int main()
{
    srand(time(NULL));

    char gameboard[20][20];
    generateBoard(gameboard);
    randGenerateApple(gameboard);
    printCurrentBoard(gameboard);


    return 0;

}