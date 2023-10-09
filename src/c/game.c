#include "../../include/raylib.h"
#include "../../include/raymath.h"
#include <stdio.h>
#include <string.h>

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define NUM_FRAMES 3
#define NUM_BLOCKS 15

// Function prototypes
Vector2 get_center(Texture2D texture);
void animation(Texture2D frames[NUM_FRAMES], int currentFrame, float frameTimer, const char *name, Vector2 position);
void load_animation(Texture2D frames[NUM_FRAMES], const char *name);
bool IsMouseOverBox(Vector2 mousePosition, Vector2 boxPosition, Texture2D Box);
void CopyImage(Vector2 *imagePosition, Vector2 targetPosition, Texture2D image);
void InitializeGame(void);
void UpdateGame(void);
void DrawGame(void);
void UnloadGame(void);

// Global variables
char Laika[] = "Laika";
char MegaChonker[] = "MegaChonker";
Texture2D box_size = {250, 250};
Texture2D LaikaFrames[3];
Texture2D MegaChonkerFrames[3];
Texture2D bg_yard;
Texture2D Laika1;
Texture2D MegaChonker1;
int currentFrame = 0;
float frameTimer = 0;
float frameSpeed = 0.3f;
Vector2 imagePosition = {0, 0};
Vector2 targetPositions[NUM_BLOCKS];
Vector2 targetPosition = {0, 0};
Vector2 targetPosition2 = {0, 0};
Color brownColor_Laika = BROWN;
Color brownColor_MC = BROWN;
bool shouldCopyLaika = false;
bool shouldCopyMC = false;
bool block_empty[NUM_BLOCKS];
bool block_contains_Laika_animation[NUM_BLOCKS];
bool block_contains_MC_animation[NUM_BLOCKS];
bool shouldDrawAnimationLaika[NUM_BLOCKS] = {false};
bool shouldDrawAnimationLaika1 = false;
bool shouldDrawAnimationLaika2 = false;
bool shouldDrawAnimationMC[NUM_BLOCKS] = {false};
bool shouldDrawAnimationMC1 = false;
bool shouldDrawAnimationMC2 = false;

int start_game(void)
{
  // Initialization
  InitializeGame();

  while (!WindowShouldClose())
  {
    // Update
    UpdateGame();

    // Draw
    DrawGame();
  }

  // Unload
  UnloadGame();

  return 0;
}

Vector2 get_center(Texture2D texture)
{
  Vector2 center;
  center.x = (float)(SCREEN_WIDTH - texture.width) / 2;
  center.y = (float)(SCREEN_HEIGHT - texture.height) / 2;
  return center;
}

void animation(Texture2D frames[NUM_FRAMES], int currentFrame, float frameTimer, const char *name, Vector2 position)
{
  Vector2 center = get_center(frames[currentFrame]);
  DrawTexture(frames[currentFrame], position.x, position.y, WHITE);
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

void CopyImage(Vector2 *imagePosition, Vector2 targetPosition, Texture2D image)
{
  *imagePosition = targetPosition;
}

void InitializeGame(void)
{
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "MeowXMonster");
  SetTargetFPS(60);

  // Load animation frames
  char Laika[] = "Laika";
  char MegaChonker[] = "MegaChonker";
  load_animation(LaikaFrames, Laika);
  load_animation(MegaChonkerFrames, MegaChonker);

  // Load background and character textures
  bg_yard = LoadTexture("assets/images/background/yard.png");
  Laika1 = LoadTexture("assets/images/avatar/Laika/Laika1.png");
  MegaChonker1 = LoadTexture("assets/images/avatar/MegaChonker/MegaChonker1.png");

  // Set initial positions for the blocks
  Vector2 blockStart = get_center(bg_yard);
  for (int i = 0; i < NUM_BLOCKS; i++)
  {
    int col = i / 3; // Columns (0 to 4)
    int row = i % 3; // Rows (0 to 2)
    targetPositions[i] = (Vector2){blockStart.x + (col * 250), blockStart.y + (row * 250)};
    block_empty[i] = true;
    block_contains_Laika_animation[i] = false;
    block_contains_MC_animation[i] = false;
  }

  // Set initial positions
  targetPosition = get_center(bg_yard);
  targetPosition2 = (Vector2){get_center(bg_yard).x, get_center(bg_yard).y + 250};
}

void UpdateGame(void)
{
  // Update animation frame
  frameTimer += GetFrameTime();
  if (frameTimer >= frameSpeed)
  {
    frameTimer = 0;
    currentFrame = (currentFrame + 1) % 3; // Cycle through frames
  }

  Vector2 mousePosition = GetMousePosition();

  if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
  {
    for (int i = 0; i < NUM_BLOCKS; i++)
    {
      if (IsMouseOverBox(mousePosition, (Vector2){0, 0}, Laika1))
      {
        shouldCopyLaika = true;
        shouldCopyMC = false;
        brownColor_Laika = DARKBROWN;
        brownColor_MC = BROWN;
        printf("Block %d is %s\n", i, block_empty[i] ? "empty" : "occupied");
      }
      else if (IsMouseOverBox(mousePosition, (Vector2){0, 250}, MegaChonker1))
      {
        shouldCopyLaika = false;
        shouldCopyMC = true;
        brownColor_Laika = BROWN;
        brownColor_MC = DARKBROWN;
        printf("Block %d is %s\n", i, block_empty[i] ? "empty" : "occupied");
      }

      else if (CheckCollisionPointRec(mousePosition, (Rectangle){targetPositions[i].x, targetPositions[i].y, 250, 250}))
      {
        printf("=====================================\n");
        if (shouldCopyLaika && block_empty[i])
        {
          CopyImage(&imagePosition, targetPositions[i], Laika1);
          shouldDrawAnimationLaika[i] = true;
          shouldDrawAnimationMC[i] = false;
          brownColor_Laika = BROWN;
          block_empty[i] = false;
          block_contains_Laika_animation[i] = true; // Mark this block as containing animation
          shouldCopyLaika = false;
        }
        else if (shouldCopyMC && block_empty[i])
        {
          CopyImage(&imagePosition, targetPositions[i], MegaChonker1);
          shouldDrawAnimationLaika[i] = false;
          shouldDrawAnimationMC[i] = true;
          brownColor_MC = BROWN;
          block_empty[i] = false;
          block_contains_MC_animation[i] = true; // Mark this block as containing animation
          shouldCopyMC = false;
        }
        else if (block_contains_Laika_animation[i]) // Check if animation is present
        {
          shouldDrawAnimationLaika[i] = true; // Re-draw the animation
          shouldDrawAnimationMC[i] = false;
        }
        else if (block_contains_MC_animation[i]) // Check if animation is present
        {
          shouldDrawAnimationLaika[i] = false; // Re-draw the animation
          shouldDrawAnimationMC[i] = true;
        }
        else
        {
          shouldDrawAnimationLaika[i] = false;
          shouldDrawAnimationMC[i] = false;
          shouldCopyLaika = false;
          shouldCopyMC = false;
          brownColor_Laika = BROWN;
          brownColor_MC = BROWN;
        }
      }
    }
  }
}

void DrawGame(void)
{
  BeginDrawing();
  ClearBackground(RAYWHITE);

  // Draw the current frame
  DrawTexture(bg_yard, get_center(bg_yard).x, get_center(bg_yard).y, WHITE);

  DrawRectangle(0, 0, 250, 250, brownColor_Laika);
  DrawRectangle(0, 250, 250, 250, brownColor_MC);
  for (int i = 0; i < NUM_BLOCKS; i++)
  {
    DrawRectangle(targetPositions[i].x, targetPositions[i].y, 250, 250, (Color){0, 255, 0, 0});

    if (shouldDrawAnimationLaika[i])
    {
      animation(LaikaFrames, currentFrame, frameTimer, Laika, targetPositions[i]);
    }

    if (shouldDrawAnimationMC[i])
    {
      animation(MegaChonkerFrames, currentFrame, frameTimer, MegaChonker, targetPositions[i]);
    }
  }

  // Draw Laika1 and MegaChonker1 here (outside the loop)
  DrawTexture(Laika1, 0, 0, WHITE);
  DrawTexture(MegaChonker1, 0, 250, WHITE);

  EndDrawing();
}

void UnloadGame(void)
{
  // Unload textures
  for (int i = 0; i < 3; i++)
  {
    UnloadTexture(LaikaFrames[i]);
    UnloadTexture(MegaChonkerFrames[i]);
  }
  UnloadTexture(bg_yard);
  UnloadTexture(Laika1);
  UnloadTexture(MegaChonker1);

  CloseWindow();
}
