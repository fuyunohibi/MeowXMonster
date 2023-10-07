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

void animation(Texture2D frames[NUM_FRAMES], int currentFrame, float frameTimer, float frameSpeed, const char *name, Vector2 position)
{
  Vector2 center = get_center(frames[currentFrame]);
  if (strcmp(name, "Laika") == 0)
  {
    DrawTexture(frames[currentFrame], position.x, position.y, WHITE);
  }
  else if (strcmp(name, "MegaChonker") == 0)
  {
    DrawTexture(frames[currentFrame], position.x, position.y, WHITE);
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

bool IsMouseOverBox(Vector2 mousePosition, Vector2 boxPosition, Texture2D Box)
{
  return CheckCollisionPointRec(mousePosition, (Rectangle){boxPosition.x, boxPosition.y, Box.width, Box.height});
}

// Function to copy the image to a new position
void CopyImage(Vector2 *imagePosition, Vector2 targetPosition, Texture2D image)
{
  *imagePosition = targetPosition;
}

int start_game(void)
{

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "MeowXMonster");
  SetTargetFPS(60);

  Texture2D box_size = {250, 250};

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
  Texture2D MegaChonker1 = LoadTexture("assets/images/avatar/MegaChonker/MegaChonker1.png");

  int currentFrame = 0;
  float frameTimer = 0;
  float frameSpeed = 0.3f; // Adjust this to control animation speed

  SetTargetFPS(60);

  Vector2 imagePosition = {0, 0};                                              // Initial position of the image
  Vector2 targetPosition = {(get_center(bg_yard)).x, (get_center(bg_yard)).y}; // Initial position of the green rectangle
  Vector2 targetPosition2 = {(get_center(bg_yard)).x, (get_center(bg_yard)).y + 251};
  Color brownColor_Laika = BROWN;
  Color brownColor_MC = BROWN;

  bool shouldCopyLaika = false;
  bool shouldCopyMC = false;

  bool shouldDrawAnimationLaika1 = false;
  bool shouldDrawAnimationLaika2 = false;
  bool shouldDrawAnimationMC1 = false;
  bool shouldDrawAnimationMC2 = false;

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
      if (IsMouseOverBox(mousePosition, (Vector2){0, 0}, Laika1))
      {
        shouldCopyLaika = true;
        shouldCopyMC = false;
        brownColor_Laika = DARKBROWN;
        brownColor_MC = BROWN;
      }
      else if (IsMouseOverBox(mousePosition, (Vector2){0, 251}, MegaChonker1))
      {
        shouldCopyLaika = false;
        shouldCopyMC = true;
        brownColor_Laika = BROWN;
        brownColor_MC = DARKBROWN;
      }
      else if (IsMouseOverBox(mousePosition, (Vector2){0, 251}, box_size))
      {
        brownColor_MC = DARKBROWN; // Change color of the second brown rectangle
      }
      else if (CheckCollisionPointRec(mousePosition, (Rectangle){targetPosition.x, targetPosition.y, 250, 250}))
      {
        if (shouldCopyLaika)
        {
          CopyImage(&imagePosition, targetPosition, Laika1);
          shouldCopyLaika = false;
          shouldDrawAnimationLaika1 = true;
          brownColor_Laika = BROWN;
        }
        else if (shouldCopyMC)
        {
          CopyImage(&imagePosition, targetPosition, MegaChonker1);
          shouldCopyMC = false;
          shouldDrawAnimationMC1 = true;
          brownColor_MC = BROWN;
        }
      }
      else if (CheckCollisionPointRec(mousePosition, (Rectangle){targetPosition2.x, targetPosition2.y, 250, 250}))
      {
        if (shouldCopyLaika)
        {
          CopyImage(&imagePosition, targetPosition2, Laika1);
          shouldCopyLaika = false;
          shouldDrawAnimationLaika2 = true;
          brownColor_Laika = BROWN;
        }
        else if (shouldCopyMC)
        {
          CopyImage(&imagePosition, targetPosition2, MegaChonker1);
          shouldCopyMC = false;
          shouldDrawAnimationMC2 = true;
          brownColor_MC = BROWN;
        }
      }
      else
      {
        shouldCopyLaika = false;
        shouldCopyMC = false;
        brownColor_Laika = BROWN;
        brownColor_MC = BROWN;
      }
    }

    // Draw
    BeginDrawing();
    ClearBackground(RAYWHITE);

    // Draw the current frame
    DrawTexture(bg_yard, (get_center(bg_yard)).x, (get_center(bg_yard)).y, WHITE);
    // animation(MegaChonkerFrames, currentFrame, frameTimer, frameSpeed, MegaChonker, get_center(MegaChonkerFrames[0]));

    DrawRectangle(0, 0, 250, 250, brownColor_Laika);
    DrawRectangle(0, 251, 250, 250, brownColor_MC);
    DrawRectangle(targetPosition.x, targetPosition.y, 250, 250, (Color){0, 255, 0, 0});
    DrawRectangle(targetPosition2.x, targetPosition2.y, 250, 250, (Color){0, 255, 0, 0}); // Transparent green

    if (shouldDrawAnimationLaika1)
    {
      // Draw the Laika animation when it's copied
      animation(LaikaFrames, currentFrame, frameTimer, frameSpeed, Laika, targetPosition);
    }
    if (shouldDrawAnimationLaika2)
    {
      // Draw the Laika animation when it's copied
      animation(LaikaFrames, currentFrame, frameTimer, frameSpeed, Laika, targetPosition2);
    }
    if (shouldDrawAnimationMC1)
    {
      // Draw the Laika animation when it's copied
      animation(MegaChonkerFrames, currentFrame, frameTimer, frameSpeed, MegaChonker, targetPosition);
    }
    if (shouldDrawAnimationMC2)
    {
      // Draw the Laika animation when it's copied
      animation(MegaChonkerFrames, currentFrame, frameTimer, frameSpeed, MegaChonker, targetPosition2);
    }
    else
    {
      // Draw the LaikaFrames[0] (first frame) when it's not copied
      DrawTexture(LaikaFrames[0], 0, 0, WHITE);
      DrawTexture(MegaChonkerFrames[0], 0, 251, WHITE);
    }

    DrawTexture(Laika1, 0, 0, WHITE);
    DrawTexture(MegaChonker1, 0, 251, WHITE);

    EndDrawing();
  }

  // Unload textures
  for (int i = 0; i < 3; i++)
  {
    UnloadTexture(LaikaFrames[i]);
    UnloadTexture(MegaChonkerFrames[i]);
  }
  UnloadTexture(bg_yard);
  UnloadTexture(Laika1);

  CloseWindow();

  return 0;
}
