#include <vector>
#include <raylib.h>

class Cell {
  public:
    // Default ctor
    Cell();

    // Sets cell's col and row to specified col and row
    Cell(int col, int row);

    // Draw one cell to screen
    void draw(int cellWidth, int cellHeight);

    // Return false if flagged or revealed, reveals cell and returns true otherwise
    bool reveal();

    // Toggle flag
    void flag();

    // Set mine to true
    void set_mine();

    // Set checkedRecursively to true
    void check_cell();

    // Set nearMines
    void set_near_mines(int numNearMines);

    // Return if cell has a mine
    bool is_mine() const;

    // Return if cell has been revealed
    bool is_revealed() const;

    // Return if cell is flagged
    bool is_flagged() const;

    // Return if cell has no neighboring mines
    bool is_alone() const;

    // Return if cell has not been checked
    bool was_not_checked() const;

    // Return number of neighboring mines
    int num_near_mines() const;

  private:
    int col;
    int row;
    bool mine;
    bool revealed;
    bool flagged;
    bool checkedRecursively;
    int nearMines;
};