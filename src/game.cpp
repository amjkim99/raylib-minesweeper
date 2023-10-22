#include "game.hpp"

Game::Game() : grid(), state(TITLE), numRevealed(0), numMines(0) {};

Game::~Game() {
  for (auto row : grid) {
    for (auto col : row) {
      delete col;
    }
  }
}

void Game::init_game() {
  grid.clear();
  init_grid();
  state = TITLE;
  numRevealed = 0;
  timeStart = GetTime();
  flagSprite = LoadTexture("resources/flag.png");
  mineSprite = LoadTexture("resources/mine.png");
}

void Game::init_grid() {
  for (size_t i = 0; i < ROWS; i++) {
    std::vector<Cell*> row;
    grid.push_back(row);
  }

  size_t row = 0;
  for (auto &itrRow : grid) {
    for (size_t col = 0; col < COLS; col++) {
      Cell* cell = new Cell(col, row);
      itrRow.push_back(cell);
    }
    row++;
  }
}

void Game::init_mines(int startCol, int startRow) {
  numMines = static_cast<int>(ROWS * COLS * MINE_PERCENT);
  int col;
  int row;

  for (size_t mines = numMines; mines > 0;) {
    col = rand() % COLS;
    row = rand() % ROWS;
    if (!grid[col][row]->is_mine() &&
        (col > startCol + 1 || col < startCol - 1) &&
        (row > startRow + 1 || row < startRow - 1)) {
      grid[col][row]->set_mine();
      mines--;
    }
  }

  init_mine_counts();
}

void Game::init_mine_counts() {
  for (size_t row = 0; row < ROWS; row++) {
    for (size_t col = 0; col < COLS; col++) {
      if (!grid[col][row]->is_mine()) {
        grid[col][row]->set_near_mines(count_near_mines(col, row));
      }
    }
  }
}

int Game::count_near_mines(int col, int row) {
  int mineCount = 0;
  for (int colOffset = -1; colOffset <= 1; colOffset++) {
    for (int rowOffset = -1; rowOffset <= 1; rowOffset++) {
      if (colOffset == 0 && rowOffset == 0) {
        continue;
      }
      if (!validIndex(col + colOffset, row + rowOffset)) {
        continue;
      }
      if (grid[col + colOffset][row + rowOffset]->is_mine()) {
        mineCount++;
      }
    }
  }
  return mineCount;
}

void Game::draw_title() {
  draw_grid();
  DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Fade(WHITE, 0.8));
  DrawText("MINESWEEPER", SCREEN_WIDTH / 2 - MeasureText("MINESWEEPER", 60) / 2, SCREEN_HEIGHT / 2 - 52, 60, DARKGRAY);
  DrawText("By amjkim", SCREEN_WIDTH / 2 - MeasureText("By amjkim", 30) / 2, SCREEN_HEIGHT / 2, 30, DARKGRAY);
  DrawText("Click anywhere to play", SCREEN_WIDTH / 2 - MeasureText("Click anywhere to play", 20) / 2, SCREEN_HEIGHT * 0.75 - 10, 20, DARKGRAY);
}

void Game::draw_grid() {
  ClearBackground(RAYWHITE);
  for (size_t row = 0; row < ROWS; row++) {
    for (size_t col = 0; col < COLS; col++) {
      if (grid[col][row]->is_flagged()) {
        draw_image(col, row, flagSprite.width, flagSprite.height, flagSprite);
      }
      grid[col][row]->draw(CELL_WIDTH, CELL_HEIGHT);
    }
  }
}

void Game::draw_image(int col, int row, float imageWidth, float imageHeight, Texture2D image) {
  Rectangle source = {0, 0, imageWidth, imageHeight};
  Rectangle dest = {static_cast<float>(col * CELL_WIDTH), static_cast<float>(row * CELL_HEIGHT),
                    static_cast<float>(CELL_WIDTH), static_cast<float>(CELL_HEIGHT)};
  Vector2 origin = {0, 0};

  DrawTexturePro(image, source, dest, origin, 0.0f, Fade(WHITE, 0.5f));
}

void Game::first_click() {
  Vector2 mPos = GetMousePosition();
  int col = mPos.x / CELL_WIDTH;
  int row = mPos.y / CELL_HEIGHT;

  init_mines(col, row);
  state = PLAYING;
  reveal_cell(col, row);
}

void Game::left_click() {
  Vector2 mPos = GetMousePosition();
  int col = mPos.x / CELL_WIDTH;
  int row = mPos.y / CELL_HEIGHT;

  if (state == PLAYING && validIndex(col, row) && !grid[col][row]->is_flagged()) {
    reveal_cell(col, row);
  }
  //debug();
}

void Game::right_click() {
  Vector2 mPos = GetMousePosition();
  int col = mPos.x / CELL_WIDTH;
  int row = mPos.y / CELL_HEIGHT;

  if (state == PLAYING && validIndex(col, row)) {
    grid[col][row]->flag();
  }
}

void Game::reveal_cell(int col, int row) {
  if (grid[col][row]->reveal()) {
    numRevealed++;
  }

  if (grid[col][row]->is_mine()) {
    state = LOSE;
    timeEnd = GetTime();
  }
  else {
    if (grid[col][row]->is_alone()) {
      reveal_neighbors(col, row);
    }
    if (numRevealed >= (ROWS * COLS - numMines)) {
      state = WIN;
      timeEnd = GetTime();
    }
  }
}

void Game::reveal_neighbors(int col, int row) {
  for (int rowOffset = -1; rowOffset <= 1; rowOffset++) {
    for (int colOffset = -1; colOffset <= 1; colOffset++) {
      if (rowOffset == 0 && colOffset == 0) {
        continue;
      }
      if (!validIndex(col + colOffset, row + rowOffset)) {
        continue;
      }
      if (grid[col + colOffset][row + rowOffset]->was_not_checked()) {
        grid[col + colOffset][row + rowOffset]->check_cell();
        reveal_cell(col + colOffset, row + rowOffset);
      }
    }
  }
}

void Game::reveal_and_draw_mines() {
  for (size_t row = 0; row < ROWS; row++) {
    for (size_t col = 0; col < COLS; col++) {
      if (grid[col][row]->is_mine()) {
        grid[col][row]->reveal();
        draw_image(col, row, mineSprite.width, mineSprite.height, mineSprite);
      }
    }
  }
}

void Game::lose() {
  draw_grid();
  reveal_and_draw_mines();

  DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Fade(WHITE, 0.8));
  DrawText("YOU LOSE", SCREEN_WIDTH / 2 - MeasureText("YOU LOSE", 40) / 2, SCREEN_HEIGHT / 2 - 10, 40, DARKGRAY);
  DrawText("Press 'r' to play again", SCREEN_WIDTH / 2 - MeasureText("Press 'r' to play again", 20) / 2, SCREEN_HEIGHT * 0.75 - 10, 20, DARKGRAY);

  int minutes = static_cast<int>(timeEnd - timeStart) / 60;
  int seconds = static_cast<int>(timeEnd - timeStart) % 60;
  DrawText(TextFormat("Time played: %d minutes, %d seconds.", minutes, seconds), 20, SCREEN_HEIGHT - 40, 20, DARKGRAY);
}

void Game::win() {
  draw_grid();
  reveal_and_draw_mines();

  DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Fade(WHITE, 0.8));
  DrawText("YOU WIN", SCREEN_WIDTH / 2 - MeasureText("YOU WIN", 40) / 2, SCREEN_HEIGHT / 2 - 10, 40, DARKGRAY);
  DrawText("Press 'r' to play again", SCREEN_WIDTH / 2 - MeasureText("Press 'r' to play again", 20) / 2, SCREEN_HEIGHT * 0.75 - 10, 20, DARKGRAY);

  int minutes = static_cast<int>(timeEnd - timeStart) / 60;
  int seconds = static_cast<int>(timeEnd - timeStart) % 60;
  DrawText(TextFormat("Time played: %d minutes, %d seconds.", minutes, seconds), 20, SCREEN_HEIGHT - 40, 20, DARKGRAY);
}

GameState Game::check_state() const {
  return state;
}

bool Game::validIndex(int col, int row) const {
  return col >= 0 && col < COLS && row >= 0 && row < ROWS;
}

void Game::debug() const {
  std::cout << "-----DEBUGGING-----\n\n";
  std::cout << "MINE COUNT: " << numMines << "\n";
  std::cout << "MINE LOCATIONS:\n";
  for (size_t row = 0; row < ROWS; row++) {
    for (size_t col = 0; col < COLS; col++) {
      std::cout << (grid[col][row]->is_mine()) << " ";
    }
    std::cout << "\n";
  }

  std::cout << "\nNEARBY MINE COUNTS:\n";
  for (size_t row = 0; row < ROWS; row++) {
    for (size_t col = 0; col < COLS; col++) {
      std::cout << (grid[col][row]->num_near_mines()) << " ";
    }
    std::cout << "\n";
  }

  std::cout << "\nCHECKED:\n";
  for (size_t row = 0; row < ROWS; row++) {
    for (size_t col = 0; col < COLS; col++) {
      std::cout << (!grid[col][row]->was_not_checked()) << " ";
    }
    std::cout << "\n";
  }
}