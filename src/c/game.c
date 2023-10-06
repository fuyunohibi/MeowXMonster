#include "../../include/raylib.h"
#include "../../include/raymath.h"
#include <stdio.h>
#include <string.h>

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define NUM_FRAMES 3

Vector2 get_center(Texture2D texture)
{
  Vector2 center;
  center.x = (float)(SCREEN_WIDTH - texture.width) / 2;
  center.y = (float)(SCREEN_HEIGHT - texture.height) / 2;
  return center;
}

void animation(Texture2D frames[NUM_FRAMES], int currentFrame, float frameTimer, float frameSpeed, const char *name)
{
  Vector2 center = get_center(frames[currentFrame]);
  if (strcmp(name, "Laika") == 0)
  {
    DrawTexture(frames[currentFrame], center.x, center.y, WHITE);
  }
  else if (strcmp(name, "MegaChonker") == 0)
  {
    DrawTexture(frames[currentFrame], center.x - (250 * 2), center.y, WHITE);
    DrawTexture(frames[currentFrame], center.x + (250 * 2), center.y, WHITE);
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

bool IsMouseOverBox(Vector2 mousePosition, Vector2 imagePosition, Texture2D Box)
{
  return CheckCollisionPointRec(mousePosition, (Rectangle){imagePosition.x, imagePosition.y, Box.width, Box.height});
}

// Function to copy the image to a new position
void CopyLaikaImage(Vector2 *imagePosition, Vector2 targetPosition, Texture2D image)
{
  *imagePosition = targetPosition;
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
  Texture2D Laika1 = LoadTexture("assets/images/avatar/Laika/Laika1.png");

  int currentFrame = 0;
  float frameTimer = 0;
  float frameSpeed = 0.3f; // Adjust this to control animation speed

  SetTargetFPS(60);

  Vector2 imagePosition = {0, 0};                                              // Initial position of the image
  Vector2 targetPosition = {(get_center(bg_yard)).x, (get_center(bg_yard)).y}; // Initial position of the green rectangle
  bool shouldCopyImage = false;
  Color brownColor = BROWN;

  while (!WindowShouldClose())
  {
    // Update
    frameTimer += GetFrameTime();
    if (frameTimer >= frameSpeed)
    {
      frameTimer = 0;
      currentFrame = (currentFrame + 1) % 3; // Cycle through frames
    }

    Vector2 mousePosition = GetMousePosition();

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
      if (IsMouseOverBox(mousePosition, imagePosition, Laika1))
      {
        shouldCopyImage = true;
        brownColor = DARKBROWN;
      }
      else if (CheckCollisionPointRec(mousePosition, (Rectangle){targetPosition.x, targetPosition.y, 285, 285}) && shouldCopyImage)
      {
        CopyLaikaImage(&imagePosition, targetPosition, Laika1);
        shouldCopyImage = false;
        brownColor = BROWN;
      }
    }

    // Draw
    BeginDrawing();
    ClearBackground(RAYWHITE);

    // Draw the current frame
    DrawTexture(bg_yard, (get_center(bg_yard)).x, (get_center(bg_yard)).y, WHITE);
    animation(LaikaFrames, currentFrame, frameTimer, frameSpeed, Laika);
    animation(MegaChonkerFrames, currentFrame, frameTimer, frameSpeed, MegaChonker);

    DrawRectangle(0, 0, 250, 250, brownColor);
    DrawRectangle(targetPosition.x, targetPosition.y, 250, 250, (Color){0, 255, 0, 0}); // Transparent green

    DrawTexture(Laika1, 0, 0, WHITE);
    DrawTexture(Laika1, imagePosition.x, imagePosition.y, WHITE);

    EndDrawing();
  }

  // Unload textures
  for (int i = 0; i < 3; i++)
  {
    UnloadTexture(LaikaFrames[i]);
    UnloadTexture(MegaChonkerFrames[i]);
  }
  UnloadTexture(bg_yard);

  CloseWindow();

  return 0;
}
