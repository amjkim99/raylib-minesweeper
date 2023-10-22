#include "cell.hpp"


Cell::Cell()
  : col(0), row(0), mine(false), revealed(false),
    flagged(false), checkedRecursively(false), nearMines(9) { }

Cell::Cell(int col, int row)
  : col(col), row(row), mine(false), revealed(false),
    flagged(false), checkedRecursively(false), nearMines(9) { }

void Cell::draw(int cellWidth, int cellHeight,
                int flagWidth, int flagHeight, Texture2D flagSprite) {
  if (revealed) {
    if (mine) {
      DrawRectangle(row * cellWidth, col * cellHeight, cellWidth, cellHeight, RED);
    }
    else {
      DrawRectangle(row * cellWidth, col * cellHeight, cellWidth, cellHeight, LIGHTGRAY);
      if (nearMines > 0)
			{
				DrawText(TextFormat("%d", nearMines),
                 row * cellWidth + 12, col * cellHeight + 4, cellHeight - 8, DARKGRAY);
			}
    }
  }
  else if (flagged) {
    Rectangle source = {0, 0, static_cast<float>(flagWidth), static_cast<float>(flagHeight)};
    Rectangle dest = {static_cast<float>(row * cellWidth), static_cast<float>(col * cellHeight),
                      static_cast<float>(cellWidth), static_cast<float>(cellHeight)};
    Vector2 origin = {0, 0};

    DrawTexturePro(flagSprite, source, dest, origin, 0.0f, Fade(WHITE, 0.5f));
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

bool Cell::is_mine() {
  return mine;
}

bool Cell::is_flagged() {
  return flagged;
}

bool Cell::is_alone() {
  return (nearMines == 0);
}

bool Cell::was_not_checked() {
  return !checkedRecursively;
}

int Cell::num_near_mines() {
  return nearMines;
}