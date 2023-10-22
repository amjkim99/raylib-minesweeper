#include <raylib.h>
#include "game.hpp"

int main() {
  srand(time(0));
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Minesweeper by amjkim");
  SetTargetFPS(60);

  Game game;
  game.init_game();

  while (!WindowShouldClose()) {
    // Reset game if R is pressed at any time
    if (IsKeyPressed(KEY_R)) {
      game.init_game();
    }

    // Check state & handle inputs
    switch(game.check_state()) {
      case TITLE:
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
          game.first_click();
        }
        break;
      case PLAYING:
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
          game.left_click();
        }
        else if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
          game.right_click();
        }
        break;
      case LOSE:
        game.lose();
        break;
      case WIN:
        game.win();
        break;
    }

    // Draw screen
    BeginDrawing();
    switch(game.check_state()) {
      case TITLE:
        game.draw_title();
        break;
      case PLAYING:
        game.draw_grid();
        break;
      case LOSE:
        game.lose();
        break;
      case WIN:
        game.win();
        break;
    }
    EndDrawing();
  }

  CloseWindow();
  return 0;
}