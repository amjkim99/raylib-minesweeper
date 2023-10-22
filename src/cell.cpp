#include "cell.hpp"


Cell::Cell()
  : col(0), row(0), mine(false), revealed(false),
    flagged(false), checkedRecursively(false), nearMines(9) { }

Cell::Cell(int col, int row)
  : col(col), row(row), mine(false), revealed(false),
    flagged(false), checkedRecursively(false), nearMines(9) { }

void Cell::draw(int cellWidth, int cellHeight) {
  if (revealed) {
    DrawRectangle(row * cellWidth, col * cellHeight, cellWidth, cellHeight, LIGHTGRAY);
    if (nearMines > 0 && nearMines < 9) {
      DrawText(TextFormat("%d", nearMines), row * cellWidth + 12, col * cellHeight + 4, cellHeight - 8, DARKGRAY);
    }
  }

  DrawRectangleLines(row * cellWidth, col * cellHeight, cellWidth, cellHeight, BLACK);
}

bool Cell::reveal() {
  if (flagged || revealed) {
    return false;
  }
  revealed = true;
  return true;
}

void Cell::flag() {
  flagged = !flagged;
}

void Cell::set_mine() {
  mine = true;
}

void Cell::check_cell() {
  checkedRecursively = true;
}

void Cell::set_near_mines(int numNearMines) {
  nearMines = numNearMines;
}

bool Cell::is_mine() const {
  return mine;
}
bool Cell::is_revealed() const {
  return revealed;
}

bool Cell::is_flagged() const {
  return flagged;
}

bool Cell::is_alone() const {
  return (nearMines == 0);
}

bool Cell::was_not_checked() const {
  return !checkedRecursively;
}

int Cell::num_near_mines() const {
  return nearMines;
}