#include "../../include/raylib.h"
#include "../../include/raymath.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int start_game(void) {

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "My raylib game");
  SetTargetFPS(60);

  while (!WindowShouldClose())
  {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawText("Welcome to MeowXMonster!", 10, 10, 20, LIGHTGRAY);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
