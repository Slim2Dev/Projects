#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

void printCurrentBoard(char _gameBoard[][3])
{
    for (int i = 0; i < 3; i++)
    {
        cout << "\n";
        for (int j = 0; j < 3; j++)
        {
            cout << " " << _gameBoard[i][j] << " ";
        }
    }
    cout << "\n";
}

bool checkIfWinning(char _gameBoard[][3])
{
    // Rows and columns
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

    // Diagonals
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

void player1Move(char _gameBoard[][3], int _randPlayerSymbol)
{
    int coll_x, row_y;
    char symbol = (_randPlayerSymbol == 1) ? 'X' : 'O';

    while (!checkIfWinning(_gameBoard) && !checkIfBoardFull(_gameBoard))
    {
        cout << "Player 1 (" << symbol << ") - enter column and row (0-2): ";
        cin >> coll_x >> row_y;

        if (coll_x < 0 || coll_x >= 3 || row_y < 0 || row_y >= 3)
        {
            cout << "Out of bounds! Enter two numbers from 0 to 2.\n";
            continue;
        }

        if (_gameBoard[row_y][coll_x] == '.')
        {
            _gameBoard[row_y][coll_x] = symbol;
            break;
        }
        else
        {
            cout << "That spot is already taken!\n";
        }
    }
}

void player2Move(char _gameBoard[][3], int _randPlayerSymbol)
{
    int coll_x, row_y;
    char symbol = (_randPlayerSymbol == 1) ? 'O' : 'X';

    while (!checkIfWinning(_gameBoard) && !checkIfBoardFull(_gameBoard))
    {
        cout << "Player 2 (" << symbol << ") - enter column and row (0-2): ";
        cin >> coll_x >> row_y;

        if (coll_x < 0 || coll_x >= 3 || row_y < 0 || row_y >= 3)
        {
            cout << "Out of bounds! Enter two numbers from 0 to 2.\n";
            continue;
        }

        if (_gameBoard[row_y][coll_x] == '.')
        {
            _gameBoard[row_y][coll_x] = symbol;
            break;
        }
        else
        {
            cout << "That spot is already taken!\n";
        }
    }
}

int main()
{
    srand(time(NULL));

    int randPlayerSymbol = rand() % 2;

    char gameBoard[3][3] = {
        {'.', '.', '.'},
        {'.', '.', '.'},
        {'.', '.', '.'}
    };

    while (true)
    {
        printCurrentBoard(gameBoard);
        player1Move(gameBoard, randPlayerSymbol);

        if (checkIfWinning(gameBoard))
        {
            printCurrentBoard(gameBoard);
            cout << "Player 1 wins!\n";
            break;
        }
        if (checkIfBoardFull(gameBoard))
        {
            printCurrentBoard(gameBoard);
            cout << "Draw!\n";
            break;
        }

        printCurrentBoard(gameBoard);
        player2Move(gameBoard, randPlayerSymbol);

        if (checkIfWinning(gameBoard))
        {
            printCurrentBoard(gameBoard);
            cout << "Player 2 wins!\n";
            break;
        }
        if (checkIfBoardFull(gameBoard))
        {
            printCurrentBoard(gameBoard);
            cout << "Draw!\n";
            break;
        }
    }

    return 0;
}