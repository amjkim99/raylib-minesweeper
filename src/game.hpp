#pragma once
#include <raylib.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <iostream>
#include <vector>
#include "cell.hpp"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;

const int ROWS = 16;
const int COLS = 16;
const float MINE_PERCENT = 0.15;

const int CELL_WIDTH = SCREEN_WIDTH / COLS;
const int CELL_HEIGHT = SCREEN_HEIGHT / ROWS;

enum GameState {
  TITLE = 0,
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

    // Fill MINE_PERCENT of the grid with mines
    // everywhere but (startCol, startRow)
    void init_mines(int startCol, int startRow);

    // Set # of neighboring mines for cells in grid
    void init_mine_counts();

    // Return # of neighboring mines
    int count_near_mines(int col, int row);

    // Draw title screen
    void draw_title();

    // Draw grid
    void draw_grid();

    // Draw a Texture2D image at (col, row)
    void draw_image(int col, int row, float imageWidth, float imageHeight, Texture2D image);

    // Initialize mines with first click
    // Set game state to playing
    // Reveal clicked cell
    void first_click();

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
    void reveal_and_draw_mines();

    // Reveal mines and print lose screen
    void lose();

    // Reveal mines and print win screen
    void win();

    // Return game state
    GameState check_state() const;

    // Check if col and row are valid indices
    bool validIndex(int col, int row) const;

    // Print debugging info to std::cout
    void debug() const;

  private:
    std::vector<std::vector<Cell*>> grid;
    GameState state;
    int numRevealed;
    int numMines;
    double timeStart;
    double timeEnd;
    Texture2D flagSprite;
    Texture2D mineSprite;
};