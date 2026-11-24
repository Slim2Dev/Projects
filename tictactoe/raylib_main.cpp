#include "raylib.h"
#include <ctime>
#include <cstdlib>

void printCurrentBoard(char _gameBoard[][3], int boardSize, int offsetY)
{
    int cellSize = boardSize / 3;

    for (int i = 1; i < 3; i++)
    {
        float pos = static_cast<float>(i * cellSize);
        DrawLineEx({pos, static_cast<float>(offsetY)}, {pos, static_cast<float>(offsetY + boardSize)}, 4.0f, DARKGRAY);
        DrawLineEx({0.0f, static_cast<float>(offsetY) + pos}, {static_cast<float>(boardSize), static_cast<float>(offsetY) + pos}, 4.0f, DARKGRAY);
    }

    int pad = cellSize / 5;
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            int x0 = col * cellSize;
            int y0 = offsetY + row * cellSize;

            if (_gameBoard[row][col] == 'X')
            {
                DrawLineEx(
                    {static_cast<float>(x0 + pad), static_cast<float>(y0 + pad)},
                    {static_cast<float>(x0 + cellSize - pad), static_cast<float>(y0 + cellSize - pad)},
                    6.0f, MAROON
                );
                DrawLineEx(
                    {static_cast<float>(x0 + cellSize - pad), static_cast<float>(y0 + pad)},
                    {static_cast<float>(x0 + pad), static_cast<float>(y0 + cellSize - pad)},
                    6.0f, MAROON
                );
            }
            else if (_gameBoard[row][col] == 'O')
            {
                float cx = static_cast<float>(x0 + cellSize / 2);
                float cy = static_cast<float>(y0 + cellSize / 2);
                float radius = static_cast<float>(cellSize / 2 - pad);
                DrawRing({cx, cy}, radius - 6.0f, radius, 0.0f, 360.0f, 36, DARKBLUE);
            }
        }
    }
}

bool checkIfWinning(char _gameBoard[][3])
{
    for (int i = 0; i < 3; i++)
    {
        if (_gameBoard[i][0] != '.' &&
            _gameBoard[i][0] == _gameBoard[i][1] &&
            _gameBoard[i][1] == _gameBoard[i][2])
        {
            return true;
        }

        if (_gameBoard[0][i] != '.' &&
            _gameBoard[0][i] == _gameBoard[1][i] &&
            _gameBoard[1][i] == _gameBoard[2][i])
        {
            return true;
        }
    }

    if (_gameBoard[0][0] != '.' &&
        _gameBoard[0][0] == _gameBoard[1][1] &&
        _gameBoard[1][1] == _gameBoard[2][2])
    {
        return true;
    }

    if (_gameBoard[0][2] != '.' &&
        _gameBoard[0][2] == _gameBoard[1][1] &&
        _gameBoard[1][1] == _gameBoard[2][0])
    {
        return true;
    }

    return false;
}

bool checkIfBoardFull(char _gameBoard[][3])
{
    int countFullSlots = 0;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (_gameBoard[i][j] == 'X' || _gameBoard[i][j] == 'O')
            {
                countFullSlots++;
            }
        }
    }

    return countFullSlots == 9;
}

void resetBoard(char _gameBoard[][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            _gameBoard[i][j] = '.';
        }
    }
}

int main()
{
    const int boardSize = 600;
    const int topBarHeight = 70;
    const int bottomBarHeight = 50;

    InitWindow(boardSize, boardSize + topBarHeight + bottomBarHeight, "Tic-Tac-Toe - raylib");
    SetTargetFPS(60);

    srand(static_cast<unsigned int>(time(NULL)));

    char gameBoard[3][3];
    resetBoard(gameBoard);

    int randPlayerSymbol = rand() % 2;
    char player1Symbol = (randPlayerSymbol == 1) ? 'X' : 'O';
    char player2Symbol = (randPlayerSymbol == 1) ? 'O' : 'X';

    int currentPlayer = 1;
    bool gameOver = false;
    const char* statusText = "";

    auto startNewMatch = [&]() {
        resetBoard(gameBoard);
        randPlayerSymbol = rand() % 2;
        player1Symbol = (randPlayerSymbol == 1) ? 'X' : 'O';
        player2Symbol = (randPlayerSymbol == 1) ? 'O' : 'X';
        currentPlayer = 1;
        gameOver = false;
        statusText = "";
    };

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_R))
        {
            startNewMatch();
        }

        if (!gameOver && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            Vector2 mouse = GetMousePosition();
            if (mouse.y >= topBarHeight && mouse.y < topBarHeight + boardSize &&
                mouse.x >= 0 && mouse.x < boardSize)
            {
                int cellSize = boardSize / 3;
                int col = static_cast<int>(mouse.x) / cellSize;
                int row = static_cast<int>(mouse.y - topBarHeight) / cellSize;

                if (gameBoard[row][col] == '.')
                {
                    char currentSymbol = (currentPlayer == 1) ? player1Symbol : player2Symbol;
                    gameBoard[row][col] = currentSymbol;

                    if (checkIfWinning(gameBoard))
                    {
                        gameOver = true;
                        statusText = (currentPlayer == 1) ? "Player 1 wins!" : "Player 2 wins!";
                    }
                    else if (checkIfBoardFull(gameBoard))
                    {
                        gameOver = true;
                        statusText = "Draw!";
                    }
                    else
                    {
                        currentPlayer = (currentPlayer == 1) ? 2 : 1;
                    }
                }
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        char currentSymbol = (currentPlayer == 1) ? player1Symbol : player2Symbol;
        const char* topMessage = gameOver
            ? statusText
            : TextFormat("Player %d (%c) turn", currentPlayer, currentSymbol);

        DrawText(topMessage, 20, 22, 28, BLACK);

        printCurrentBoard(gameBoard, boardSize, topBarHeight);

        DrawText("Click a square to play | Press R to restart", 20, topBarHeight + boardSize + 15, 20, GRAY);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}