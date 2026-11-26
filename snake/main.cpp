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

    void initSnake()
    {
        snakeBody.clear();

        snakeBody.push_back({10, 10});
        snakeBody.push_back({10,9});
        snakeBody.push_back({10, 8});

        drawSnake();
    }

    void drawSnake()
    {
        for(size_t i=0; i<snakeBody.size(); i++)
        {
            int x = snakeBody[i].cor_x;
            int y = snakeBody[i].cor_y;

            if(x >= 0 && x < 20 && y >= 0 && y < 20)
            {
                _gameboard[x][y] = (i == 0) ? 'O' : 'o';
            }
        }
    }

    void moveSnake(char direction, bool grow = false)
    {
        if(snakeBody.empty()) return;

        s newHead = snakeBody[0];

        if(direction == 'w') newHead.cor_x--; // Up
        if(direction == 's') newHead.cor_x++; // Down
        if(direction == 'a') newHead.cor_y--; // Left
        if(direction == 'd') newHead.cor_y++; // Right

        if(isWallCollision(newHead))
        {
            cout << endl << "Game over!";
            return;
        }

        if(!grow)
        {
            s tail = snakeBody.back();
            _gameboard[tail.cor_x][tail.cor_y] = '.';
            snakeBody.pop_back();
        }

        snakeBody.insert(snakeBody.begin(), newHead);

        drawSnake();
    }

    bool isWallCollision(const s& head) const
    {
        return head.cor_x < 0 || head.cor_x >= 20 || 
               head.cor_y < 0 || head.cor_y >= 20;
    }
}; 






int main()
{
    srand(time(NULL));

    SnakeGame s1; 
    s1.generateBoard();
    s1.initSnake();
    s1.drawSnake();
    s1.randGenerateApple();
    s1.printCurrentBoard();
    s1.moveSnake('d');        
    s1.printCurrentBoard();
    s1.moveSnake('d', false);
    s1.printCurrentBoard(); 
    s1.moveSnake('w', true);  
    s1.printCurrentBoard();


    return 0;

}