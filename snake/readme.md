# Console Snake Game (C++)

A lightweight, console-based implementation of the classic Snake game written in C++. Currently in early development, focusing on board state management and randomized item spawning.

## Current Features

* **20×20 Grid Board:** Initializes and renders a 20×20 playing field populated with `.` representing empty tiles.
* **Apple Spawning:** Randomly selects coordinates on the board and places an apple (`A`), ensuring it only spawns on unoccupied spaces.
* **Board Space Validation:** Includes boundary/occupancy verification (`checkIfBoardHasEmptySpace()`) to prevent infinite loops when the board becomes full.
* **Console Rendering:** Cleanly formats and prints the current board state to standard output.

## Code Overview

The core logic is encapsulated within the `SnakeGame` class:

| Member / Method | Type | Description |
| :--- | :--- | :--- |
| `struct s` | Public Struct | Defines 2D coordinates (`cor_x`, `cor_y`) for tracking snake segments. |
| `_gameboard[20][20]` | Private Array | Stores the current state of each cell on the grid. |
| `snakeBody` | Private Vector | `std::vector<s>` prepared to store the snake's body coordinates. |
| `generateBoard()` | Public Method | Fills the 20×20 grid with empty space characters (`.`) and prints the initial board. |
| `printCurrentBoard()` | Public Method | Outputs the current state of `_gameboard` to the console. |
| `checkIfBoardHasEmptySpace()` | Public Method | Scans the grid and returns `true` if at least one empty cell (`.`) exists. |
| `randGenerateApple()` | Public Method | Places an apple (`A`) at a random available coordinate on the grid. |

## Getting Started

### Prerequisites
* A C++ compiler supporting C++11 or later (e.g., `g++`, `clang++`, or MSVC).

### Compilation & Execution

```bash
# Compile the source code
g++ -std=c++11 main.cpp -o snake

# Run the executable
./snake
