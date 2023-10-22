#include <raylib.h>
#include "game.hpp"

int main() {
  srand(time(0));
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Minesweeper");
  SetTargetFPS(60);

  Game game;
  game.init_game();

  while (!WindowShouldClose()) {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
      game.left_click();
    }
    else if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
      game.right_click();
    }
    if (IsKeyPressed(KEY_R)) {
      game.init_game();
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);
    game.draw_grid();

    if (game.check_state() == LOSE) {
      game.lose();
    }
    if (game.check_state() == WIN) {
      game.win();
    }
    EndDrawing();
  }

  CloseWindow();
  return 0;
}