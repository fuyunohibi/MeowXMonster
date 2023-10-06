#include "../../include/raylib.h"
#include "../../include/raymath.h"
#include <stdio.h>

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define NUM_FRAMES 3

void animation(Texture2D frames[NUM_FRAMES], int currentFrame, float frameTimer, float frameSpeed)
{
  DrawTexture(frames[currentFrame], (SCREEN_WIDTH - frames[currentFrame].width) / 2, (SCREEN_HEIGHT - frames[currentFrame].height) / 2, WHITE);
}

void load_assets(Texture2D frames[NUM_FRAMES], const char *name)
{
  char filename[256];

  for (int i = 0; i < NUM_FRAMES; i++)
  {
    sprintf(filename, "assets/images/avatar/%s/%s%d.png", name, name, i + 1);
    frames[i] = LoadTexture(filename);
  }
}

int start_game(void)
{

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "My raylib game");
  SetTargetFPS(60);

  // Load animation frames
  Texture2D frames[3];
  load_assets(frames, "Laika");

  int currentFrame = 0;
  float frameTimer = 0;
  float frameSpeed = 0.2f; // Adjust this to control animation speed

  SetTargetFPS(60);

  while (!WindowShouldClose())
  {
    // Update
    frameTimer += GetFrameTime();
    if (frameTimer >= frameSpeed)
    {
      frameTimer = 0;
      currentFrame = (currentFrame + 1) % 3; // Cycle through frames
    }

    // Draw
    BeginDrawing();
    ClearBackground(RAYWHITE);

    // Draw the current frame
    animation(frames, currentFrame, frameTimer, frameSpeed);

    EndDrawing();
  }

  // Unload textures
  for (int i = 0; i < 3; i++)
  {
    UnloadTexture(frames[i]);
  }

  CloseWindow();

  return 0;
}
