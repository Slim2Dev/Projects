#include "raylib.h"
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
                    _gameboard[rand_x][rand_y] = 'A';
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

static float getAngleFromDelta(int dRow, int dCol)
{
    if(dCol > 0) return 0.0f; 
    if(dRow > 0) return 90.0f; 
    if(dCol < 0) return 180.0f; 
    if(dRow < 0) return 270.0f; 
    return 0.0f;
}

int main()
{
    srand(static_cast<unsigned int>(time(NULL)));

    const int gridSize = 20;
    const int cellSize = 30;
    const int topBarHeight = 40;
    const int screenWidth = gridSize * cellSize;
    const int screenHeight = gridSize * cellSize + topBarHeight;

    InitWindow(screenWidth, screenHeight, "Snake - Raylib");
    Texture2D headTex = LoadTexture("assets/snake_head.png");
    Texture2D bodyTex = LoadTexture("assets/snake_body.png");
    Texture2D tailTex = LoadTexture("assets/snake_tail.png");
    Texture2D appleTex = LoadTexture("assets/apple.png");

    SetTextureFilter(headTex, TEXTURE_FILTER_POINT);
    SetTextureFilter(bodyTex, TEXTURE_FILTER_POINT);
    SetTextureFilter(tailTex, TEXTURE_FILTER_POINT);
    if (appleTex.id != 0)
    {
        SetTextureFilter(appleTex, TEXTURE_FILTER_POINT);
    }
    SetTargetFPS(60);

    SnakeGame game;
    char currentDir = 'd';
    char nextDir = 'd';

    float moveTimer = 0.0f;
    const float moveInterval = 0.14f;

    while (!WindowShouldClose())
    {
        if (!game.isGameOver())
        {
            if ((IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)) && currentDir != 's')
                nextDir = 'w';
            else if ((IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN)) && currentDir != 'w')
                nextDir = 's';
            else if ((IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT)) && currentDir != 'd')
                nextDir = 'a';
            else if ((IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT)) && currentDir != 'a')
                nextDir = 'd';

            moveTimer += GetFrameTime();
            if (moveTimer >= moveInterval)
            {
                moveTimer = 0.0f;
                currentDir = nextDir;
                game.moveSnake(currentDir);
            }
        }
        else
        {
            if (IsKeyPressed(KEY_R))
            {
                game.reset();
                currentDir = 'd';
                nextDir = 'd';
                moveTimer = 0.0f;
            }
        }

        BeginDrawing();
        ClearBackground(Color{24, 24, 28, 255});

        DrawText(TextFormat("Score: %d", game.getScore()), 12, 10, 20, RAYWHITE);
        DrawText("WASD / Arrows", screenWidth - 165, 12, 16, GRAY);

        for (int row = 0; row < gridSize; row++)
        {
            for (int col = 0; col < gridSize; col++)
            {
                int pixelX = col * cellSize;
                int pixelY = topBarHeight + row * cellSize;

                Color tileColor = ((row + col) % 2 == 0)
                                      ? Color{34, 36, 42, 255}
                                      : Color{30, 32, 38, 255};
                DrawRectangle(pixelX, pixelY, cellSize, cellSize, tileColor);

                char cell = game.getCell(row, col);
                if (cell == 'A')
                {
                    if (appleTex.id != 0)
                    {
                        Rectangle src = { 0.0f, 0.0f, (float)appleTex.width, (float)appleTex.height };
                        Rectangle dest = { (float)pixelX, (float)pixelY, (float)cellSize, (float)cellSize };
                        DrawTexturePro(appleTex, src, dest, { 0.0f, 0.0f }, 0.0f, WHITE);
                    }
                    else
                    {
                        DrawCircle(pixelX + cellSize / 2, pixelY + cellSize / 2, cellSize / 2 - 4, RED);
                    }
                }
            }
        }

        const auto& body = game.getSnakeBody();
        for (size_t i = 0; i < body.size(); i++)
        {
            int pixelX = body[i].cor_y * cellSize;
            int pixelY = topBarHeight + body[i].cor_x * cellSize;

            Texture2D tex = bodyTex;
            float rotation = 0.0f;

            if (i == 0)
            {
                tex = headTex;
                if (currentDir == 'd') rotation = 0.0f;
                else if (currentDir == 's') rotation = 90.0f;
                else if (currentDir == 'a') rotation = 180.0f;
                else if (currentDir == 'w') rotation = 270.0f;
            }
            else if (i == body.size() - 1)
            {
                tex = tailTex;
                int dRow = body[i - 1].cor_x - body[i].cor_x;
                int dCol = body[i - 1].cor_y - body[i].cor_y;
                rotation = getAngleFromDelta(dRow, dCol);
            }
            else
            {
                tex = bodyTex;
                int dRow = body[i - 1].cor_x - body[i].cor_x;
                int dCol = body[i - 1].cor_y - body[i].cor_y;
                rotation = getAngleFromDelta(dRow, dCol);
            }

            Rectangle src = { 0.0f, 0.0f, (float)tex.width, (float)tex.height };
            Rectangle dest = {
                pixelX + cellSize / 2.0f,
                pixelY + cellSize / 2.0f,
                (float)cellSize,
                (float)cellSize
            };
            Vector2 origin = { cellSize / 2.0f, cellSize / 2.0f };

            DrawTexturePro(tex, src, dest, origin, rotation, WHITE);
        }

        if (game.isGameOver())
        {
            DrawRectangle(0, topBarHeight, screenWidth, gridSize * cellSize, Color{0, 0, 0, 170});
            DrawText("GAME OVER", screenWidth / 2 - 110, screenHeight / 2 - 20, 36, RED);
            DrawText("Press R to Restart", screenWidth / 2 - 98, screenHeight / 2 + 25, 20, RAYWHITE);
        }

        EndDrawing();
    }

    if (appleTex.id != 0) UnloadTexture(appleTex);
    UnloadTexture(tailTex);
    UnloadTexture(bodyTex);
    UnloadTexture(headTex);

    CloseWindow();
    return 0;
}
