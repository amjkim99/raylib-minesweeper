#pragma once
#include <raylib.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <vector>
#include "cell.hpp"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;

const int ROWS = 16;
const int COLS = 16;
const float MINE_PERCENT = 0.1;

const int CELL_WIDTH = SCREEN_WIDTH / COLS;
const int CELL_HEIGHT = SCREEN_HEIGHT / ROWS;

enum GameState {
  PLAYING,
  LOSE,
  WIN
};

class Game {
  public:
    // Default ctor
    Game();

    // Clears grid
    ~Game();

    // Initialize game
    void init_game();

    // Initialize grid
    void init_grid();

    // Place mines in grid
    void init_mines();

    // Set # of neighboring mines for cells in grid
    void init_mine_counts();

    // Return # of neighboring mines
    int count_near_mines(int col, int row);

    // Draw grid
    void draw_grid();

    // Run reveal_cell() on clicked cell
    void left_click();

    // Toggle flag on clicked cell
    void right_click();

    // Reveals cell
    // If the cell is a mine, sets game state to LOSE
    // If the cell has no neighboring mines, recursively reveals neighbors
    // If enough cells have been revealed, sets game state to WIN
    void reveal_cell(int col, int row);

    // Reveal unchecked neighboring cells
    void reveal_neighbors(int col, int row);

    // Reveal all mines
    void reveal_mines();

    // Reveal mines and print lose screen
    void lose();

    // Reveal mines and print win screen
    void win();

    // Return game state
    GameState check_state();

    // Check if col and row are valid indices
    bool validIndex(int col, int row);

    // Print debugging info to std::cout
    void debug();

  private:
    std::vector<std::vector<Cell*>> grid;
    Texture2D flagSprite;
    GameState state;
    int numRevealed;
    int numMines;
    double timeStart;
    double timeEnd;
};