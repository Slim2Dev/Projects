#include "raylib.h"
#include <cstdlib>
#include <ctime>
#include <vector>



class SnakeGame
{
    public:
        struct s
        {
            int cor_x;
            int cor_y;
        }
    private:
        char _gameboard[20][20];
        int rand_x;
        int rand_y;
        vector<s> snakeBody;
        bool gameOver;
        int score;

    public:
        SnakeGame()
        {
            reset();
        }
        
        void reset()
        {
            gameOver = false;
            score = 0;
            clearBoard();
            initSnake();
            randGenerateApple();
        }

        void clearBoard()
        {
            for(int i=0; i<20; i++)
            {
                for(int j=0; j<20; j++)
                {
                    _gameboard[i][j] = '.';
                }
            }
        }

        bool checkIfBoardHasEmptySpace() const 
        {
            for(int i=0; i<20; i++)
            {
                for(int j=0; j<20; j++)
                {
                    if(_gameboard[i][j] == '.')
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
                    _gameboardp[rand_x][rand_y] = 'A';
                    break;
                }
            }
        }

        void initSnake()
        {
            snakeBody.clear();

            snakeBody.push_back({10,10});
            snakeBody.push_back({10, 9});
            snakeBody.push_back({10,8});

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

        bool isWallCollision(const s& head) const 
        {
            return head.cor_x < 0 || head.cor_x >= 20 ||
                   head.cor_y < 0 || head.cor_y >= 20;
        }

        bool isSelfCollision(const s& head, bool willGrow) const 
        {
            size_t checkLimit = willGrow ? snakeBody.size() : snakeBody.size() - 1;
            for(size_t i=0; i<checkLimit; i++)
            {
                if(snakeBody[i].cor_x == head.cor_x && snakeBody[i].cor_y == head.cor_y)
                {
                    return true;
                }
            }
            return false;
        }

        void moveSnake(char direction)
        {
            if(snakeBody.empty() || gameOver) return;

            s newHead = snakeBody[0];

            if(direction == 'w') newHead.cor_x--; // up
            else if(direction == 's') newHead.cor_x++; // down
            else if(direction == 'a') newHead.cor_y--; // left
            else if(direction == 'd') newHead.cor_y++; // right

            if(isWallCollision(newHead))
            {
                gameOver = true;
                return;
            }

            bool ateApple = (newHead.cor_x == rand_x && newHead. cor_y == rand_y);

            if(isSelfCollision(newHead, ateApple))
            {
                gameOver = true;
                return;
            }

            if(!ateApple)
            {
                s tail = snakeBody.back();
                _gameboard[tail.cor_x][tail.cor_y] = '.';
                snakeBody.pop_back();
            }

            snakeBody.insert(snakeBody.begin(), newHead);
            drawSnake();

            if(ateApple)
            {
                score += 10;
                randGenerateApple();
            }
        }

        char getCell(int row, int col) const 
        {
            return _gameboard[row][col];
        }

        bool isGameOver() const 
        {
            return gameOver;
        }

        int getScore() const 
        {
            return score;
        }

        const vector<s>& getSnakeBody() const 
        {
            return snakeBody;
        }
};

int main()
{

}