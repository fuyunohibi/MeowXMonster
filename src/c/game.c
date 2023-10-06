#include "../../include/raylib.h"
#include "../../include/raymath.h"
#include <stdio.h>
#include <string.h>

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define NUM_FRAMES 3

void animation(Texture2D frames[NUM_FRAMES], int currentFrame, float frameTimer, float frameSpeed, const char *name)
{
  Vector2 center = {(float)(SCREEN_WIDTH - frames[currentFrame].width) / 2, (float)(SCREEN_HEIGHT - frames[currentFrame].height) / 2};
  if (strcmp(name, "Laika") == 0)
  {
    DrawTexture(frames[currentFrame], center.x, center.y, WHITE);
  }
  else if (strcmp(name, "MegaChonker") == 0)
  {
    DrawTexture(frames[currentFrame], center.x - (285 * 2), center.y, WHITE);
    DrawTexture(frames[currentFrame], center.x + (285 * 2), center.y, WHITE);
  }
}

void load_animation(Texture2D frames[NUM_FRAMES], const char *name)
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

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "MeowXMonster");
  SetTargetFPS(60);

  // Load animation frames
  Texture2D LaikaFrames[3];
  Texture2D MegaChonkerFrames[3];
  char Laika[] = "Laika";
  char MegaChonker[] = "MegaChonker";
  load_animation(LaikaFrames, Laika);
  load_animation(MegaChonkerFrames, MegaChonker);

  // background
  Texture2D bg_yard = LoadTexture("assets/images/background/yard.png");

  int currentFrame = 0;
  float frameTimer = 0;
  float frameSpeed = 0.3f; // Adjust this to control animation speed

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
    DrawTexture(bg_yard, (SCREEN_WIDTH - bg_yard.width) / 2, ((SCREEN_HEIGHT - bg_yard.height) / 2), WHITE);
    animation(LaikaFrames, currentFrame, frameTimer, frameSpeed, Laika);
    animation(MegaChonkerFrames, currentFrame, frameTimer, frameSpeed, MegaChonker);

    EndDrawing();
  }

  // Unload textures
  for (int i = 0; i < 3; i++)
  {
    UnloadTexture(LaikaFrames[i]);
    UnloadTexture(MegaChonkerFrames[i]);
  }

  CloseWindow();

  return 0;
}
