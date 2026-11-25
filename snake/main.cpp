#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

class SnakeGame
{

    public: 

        struct s
        {
            int cor_x;
            int cor_y;
        };

    private:

        char _gameboard[20][20];
        int rand_x;
        int rand_y;
        vector<s> snakeBody;

    public:


    void generateBoard()
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

    void printCurrentBoard()
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

    bool checkIfBoardHasEmptySpace()
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

    void randGenerateApple()
    {
        while(checkIfBoardHasEmptySpace())
        {
            rand_x = rand() % 20;
            rand_y = rand() % 20;
            if(_gameboard[rand_x][rand_y] == '.')
            {
                _gameboard[rand_x][rand_y] = 'A';
                break;
            }
        }
    }
}; 




int main()
{
    srand(time(NULL));

    SnakeGame s1; 
    s1.generateBoard();
    s1.randGenerateApple();
    s1.printCurrentBoard();

    return 0;

}