#include "../../include/raylib.h"
#include "../../include/raymath.h"
#include "character/character.h"
#include <stdio.h>
#include <string.h>

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define NUM_FRAMES 3
#define NUM_BLOCKS 15
#define MAX_CHARACTERS 15
#define INITIAL_REWARD 100
#define MAX_MONSTERS 10

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
Texture2D box_size = {250, 250};
Texture2D LaikaFrames[3];
Texture2D MegaChonkerFrames[3];
Texture2D BombFrames[3];
Texture2D FartCatFrames[3];
Texture2D UfoFrames[3];
Texture2D bg;
Texture2D bg_yard;
Texture2D score_board;
Texture2D Laika1;
Texture2D MegaChonker1;
Texture2D Bomb1;
Texture2D FartCat1;
Texture2D ufo1;
int currentFrame = 0;
float frameTimer = 0;
float frameSpeed = 0.3f;
Vector2 imagePosition = {0, 0};
Vector2 targetPositions[NUM_BLOCKS];
Vector2 targetPosition = {0, 0};
Vector2 targetPosition2 = {0, 0};
Vector2 initPosition[3] = {{1920, 150}, {1920, 400}, {1920, 650}};
Color LIGHTBROWN = (Color){100, 69, 19, 128};
Color darkbrown = (Color){100, 69, 19, 200};
Color brownColor_Laika = (Color){100, 69, 19, 128};
Color brownColor_MC = (Color){100, 69, 19, 128};
Color brownColor_Bomb = (Color){100, 69, 19, 128};
Color brownColor_FC = (Color){100, 69, 19, 128};
bool shouldCopyLaika = false;
bool shouldCopyMC = false;
bool shouldCopyBomb = false;
bool shouldCopyFC = false;
bool block_empty[NUM_BLOCKS];
bool block_contains_Laika_animation[NUM_BLOCKS];
bool block_contains_MC_animation[NUM_BLOCKS];
bool block_contains_Bomb_animation[NUM_BLOCKS];
bool block_contains_FC_animation[NUM_BLOCKS];
bool shouldDrawAnimationLaika[NUM_BLOCKS] = {false};
bool shouldDrawAnimationLaika1 = false;
bool shouldDrawAnimationLaika2 = false;
bool shouldDrawAnimationMC[NUM_BLOCKS] = {false};
bool shouldDrawAnimationMC1 = false;
bool shouldDrawAnimationMC2 = false;
bool shouldDrawAnimationBomb[NUM_BLOCKS] = {false};
bool shouldDrawAnimationBomb1 = false;
bool shouldDrawAnimationBomb2 = false;
bool shouldDrawAnimationFC[NUM_BLOCKS] = {false};
bool shouldDrawAnimationFC1 = false;
bool shouldDrawAnimationFC2 = false;
Vector2 charactersPOS[MAX_CHARACTERS];
int charcount = 0;

Texture2D LaikaAtkTexture;
Texture2D FartCatAtk;

int move = 0;

typedef struct
{
  Vector2 position;
  Vector2 direction;
  float speed;
  bool active;
} Projectile;

typedef struct
{
  Vector2 position;
  bool active;
  float animationTimer;
  // Add any other UFO-related variables you need here
} UFO;

MonsterCharacter ufos[MAX_CHARACTERS];
float ufoSpawnTimer = 0.0f;
float ufoSpawnInterval = 80.0f; // Delay between UFO spawns in seconds

#define MAX_PROJECTILES 10
#define MAX_Fart 3
Projectile laikaProjectiles[MAX_PROJECTILES];
Projectile FCProjectiles[MAX_Fart];

Character charactersOnField[MAX_CHARACTERS];
int charactersCount = 0;

Character CreateCharacter(const char *name, int price, int HP, bool isAlive, int attackDamage, float attackPerSecond)
{
  Character newCharacter;
  strncpy(newCharacter.name, name, sizeof(newCharacter.name));
  newCharacter.price = price;
  newCharacter.HP = HP;
  newCharacter.isAlive = isAlive;
  newCharacter.attackDamage = attackDamage;
  newCharacter.attackPerSecond = attackPerSecond;
  newCharacter.attackTimer = 0.0f; // Initialize the attack timer

  return newCharacter;
}

void displayCharacterDetails(Character character)
{
  printf("============= Display Chracter =============\n");
  printf("Name: %s\n", character.name);
  printf("Price: %d\n", character.price);
  printf("HP: %d\n", character.HP);
  printf("isAlive: %s\n", character.isAlive ? "true" : "false");
  printf("Attack Damage: %d\n", character.attackDamage);
  printf("Attack per Second: %f\n", character.attackPerSecond);
}

MonsterCharacter CreateMonsterCharacter(MonsterCharacter *ufo, const char *name, int HP, bool isAlive, int attackDamage, float attackPerSecond)
{
  MonsterCharacter newCharacter;
  strncpy(newCharacter.name, name, sizeof(newCharacter.name));
  newCharacter.HP = HP;
  newCharacter.isAlive = isAlive;
  newCharacter.attackDamage = attackDamage;
  newCharacter.attackPerSecond = attackPerSecond;
  newCharacter.attackTimer = 0.0f; // Initialize the attack timer

  int randomIndex = GetRandomValue(0, 2);    // Randomly choose an index from 0 to 2
  ufo->position = initPosition[randomIndex]; // Use the selected position
  ufo->active = true;
  ufo->animationTimer = 0.0f;

  return newCharacter;
}

void UpdateMonsters(MonsterCharacter *ufo, float deltaTime)
{
  ufo->position.x -= 5 * deltaTime; // Move UFO to the left

  if (ufo->position.x < -UfoFrames[0].width || ufo->position.y < 0 || ufo->position.y > GetScreenHeight())
  {
    ufo->active = false; // Deactivate UFO when it goes off-screen
  }

  // Update any other UFO-related logic here
}

int start_game(void)
{
  // Initialization
  // LaikaAtkTexture = LoadTexture("assets/images/avatar/Laika/Atk/LaikaAtk.png");
  InitializeGame();
  displayCharacterDetails(Laika);
  displayCharacterDetails(MegaChonker);
  displayCharacterDetails(Bomb);
  displayCharacterDetails(FartCat);

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

void checkAliveStatus(Character *character)
{
  if (character->HP <= 0)
  {
    character->isAlive = false;
  }
}

// NOTE: For Tawan
// checkAliveStatus(&Laika);
// checkAliveStatus(&MegaChonker);

void shootProjectileFromCharacter(Character character, Vector2 position)
{
  for (int j = 0; j < MAX_PROJECTILES; j++)
  {
    if (!laikaProjectiles[j].active)
    {
      laikaProjectiles[j].position = position;         // Starting position of the projectile, modify if needed
      laikaProjectiles[j].direction = (Vector2){1, 0}; // Shoots to the right, modify if needed
      laikaProjectiles[j].speed = 5.0f;
      laikaProjectiles[j].active = true;
      break;
    }
  }
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
  // }
}

void load_animation_monster(Texture2D frames[NUM_FRAMES], const char *name)
{
  char filename[256];
  for (int i = 0; i < NUM_FRAMES; i++)
  {
    sprintf(filename, "assets/images/monster/%s/%s%d.png", name, name, i + 1);
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

Vector2 get_charPOS(Vector2 targetPosition, int charCount)
{
  Vector2 charPOS;
  charactersPOS[charCount].x = targetPosition.x + 250;
  charactersPOS[charCount].y = targetPosition.y + 125;
  return charPOS;
}

void InitializeGame(void)
{
  for (int i = 0; i < MAX_PROJECTILES; i++)
  {
    laikaProjectiles[i].active = false;
  }

  for (int i = 0; i < MAX_Fart; i++)
  {
    FCProjectiles[i].active = false;
  }
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "MeowXMonster");
  SetTargetFPS(60);

  // Initialize character
  char LaikaName[50];
  char MegaChonkerName[50];
  char BombName[50];
  char FartCatName[50];
  char ufoName[50];

  strcpy(LaikaName, Laika.name);
  strcpy(MegaChonkerName, MegaChonker.name);
  strcpy(BombName, Bomb.name);
  strcpy(FartCatName, FartCat.name);
  strcpy(ufoName, Ufo.name);

  load_animation(LaikaFrames, Laika.name);
  load_animation(MegaChonkerFrames, MegaChonker.name);
  load_animation(BombFrames, Bomb.name);
  load_animation(FartCatFrames, FartCat.name);
  load_animation_monster(UfoFrames, "ufo");

  // Load background and character textures
  bg = LoadTexture("assets/images/background/background.png");
  bg_yard = LoadTexture("assets/images/background/yard.png");
  score_board = LoadTexture("assets/images/background/Score.png");
  Laika1 = LoadTexture("assets/images/avatar/Laika/Laika1.png");
  MegaChonker1 = LoadTexture("assets/images/avatar/MegaChonker/MegaChonker1.png");
  Bomb1 = LoadTexture("assets/images/avatar/Bomb/Bomb1.png");
  FartCat1 = LoadTexture("assets/images/avatar/FartCat/FartCat1.png");
  FartCatAtk = LoadTexture("assets/images/avatar/FartCat/Atk/Fart.png");

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
    block_contains_Bomb_animation[i] = false;
    block_contains_FC_animation[i] = false;
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

  // Update projectiles
  for (int i = 0; i < MAX_PROJECTILES; i++)
  {
    if (laikaProjectiles[i].active)
    {
      laikaProjectiles[i].position.x += laikaProjectiles[i].direction.x * laikaProjectiles[i].speed;
      laikaProjectiles[i].position.y += laikaProjectiles[i].direction.y * laikaProjectiles[i].speed;

      // Check if projectile is out of bounds
      if (laikaProjectiles[i].position.x > SCREEN_WIDTH || laikaProjectiles[i].position.x < 0 ||
          laikaProjectiles[i].position.y > SCREEN_HEIGHT || laikaProjectiles[i].position.y < 0)
      {
        laikaProjectiles[i].active = false;
      }
    }
  }

  for (int i = 0; i < charactersCount; i++)
  { // Loop through all characters
    charactersOnField[i].attackTimer += GetFrameTime();

    float timeBetweenShots = 1.0f / charactersOnField[i].attackPerSecond;

    if (charactersOnField[i].attackTimer >= timeBetweenShots)
    {
      // Shoot!
      charactersOnField[i].attackTimer = 0.0f; // Reset timer
      shootProjectileFromCharacter(charactersOnField[i], charactersPOS[i]);
    }
  }
  // printf("Character count: %d\n", charactersCount);

  Vector2 mousePosition = GetMousePosition();

  if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
  {
    for (int i = 0; i < NUM_BLOCKS; i++)
    {
      if (IsMouseOverBox(mousePosition, (Vector2){0, 0}, Laika1))
      {
        shouldCopyLaika = true;
        shouldCopyMC = false;
        shouldCopyBomb = false;
        shouldCopyFC = false;
        brownColor_Laika = darkbrown;
        brownColor_MC = LIGHTBROWN;
        brownColor_Bomb = LIGHTBROWN;
        brownColor_FC = LIGHTBROWN;
        // printf("Block %d is %s\n", i, block_empty[i] ? "empty" : "occupied");
      }
      else if (IsMouseOverBox(mousePosition, (Vector2){0, 250}, MegaChonker1))
      {
        shouldCopyLaika = false;
        shouldCopyMC = true;
        shouldCopyBomb = false;
        shouldCopyFC = false;
        brownColor_Laika = LIGHTBROWN;
        brownColor_MC = darkbrown;
        brownColor_Bomb = LIGHTBROWN;
        brownColor_FC = LIGHTBROWN;
        // printf("Block %d is %s\n", i, block_empty[i] ? "empty" : "occupied");
      }
      // Bomb
      else if (IsMouseOverBox(mousePosition, (Vector2){0, 500}, Bomb1))
      {
        shouldCopyLaika = false;
        shouldCopyMC = false;
        shouldCopyBomb = true;
        shouldCopyFC = false;
        brownColor_Laika = LIGHTBROWN;
        brownColor_MC = LIGHTBROWN;
        brownColor_Bomb = darkbrown;
        brownColor_FC = LIGHTBROWN;
        // printf("Block %d is %s\n", i, block_empty[i] ? "empty" : "occupied");
      }
      else if (IsMouseOverBox(mousePosition, (Vector2){0, 750}, FartCat1))
      {
        shouldCopyLaika = false;
        shouldCopyMC = false;
        shouldCopyBomb = false;
        shouldCopyFC = true;
        brownColor_Laika = LIGHTBROWN;
        brownColor_MC = LIGHTBROWN;
        brownColor_Bomb = LIGHTBROWN;
        brownColor_FC = darkbrown;
        // printf("Block %d is %s\n", i, block_empty[i] ? "empty" : "occupied");
      }

      else if (CheckCollisionPointRec(mousePosition, (Rectangle){targetPositions[i].x, targetPositions[i].y, 250, 250}))
      {
        printf("=====================================\n");
        if (shouldCopyLaika && block_empty[i])
        {
          CopyImage(&imagePosition, targetPositions[i], Laika1);
          shouldDrawAnimationLaika[i] = true;
          shouldDrawAnimationMC[i] = false;
          shouldDrawAnimationBomb[i] = false;
          shouldDrawAnimationFC[i] = false;
          brownColor_Laika = LIGHTBROWN;
          block_empty[i] = false;
          block_contains_Laika_animation[i] = true; // Mark this block as containing animation
          shouldCopyLaika = false;
          if (charactersCount < MAX_CHARACTERS)
          {
            charactersOnField[charactersCount] = CreateCharacter("Laika", 100, 150, true, 50, 1.15);
            charactersPOS[charactersCount].x = targetPositions[i].x + 210;
            charactersPOS[charactersCount].y = targetPositions[i].y + 130;
            printf("Character %d position: %f, %f\n", charactersCount, charactersPOS[charactersCount].x, charactersPOS[charactersCount].y);
            charactersCount++;
          }
        }
        else if (shouldCopyMC && block_empty[i])
        {
          CopyImage(&imagePosition, targetPositions[i], MegaChonker1);
          shouldDrawAnimationLaika[i] = false;
          shouldDrawAnimationMC[i] = true;
          shouldDrawAnimationBomb[i] = false;
          shouldDrawAnimationFC[i] = false;
          brownColor_MC = LIGHTBROWN;
          block_empty[i] = false;
          block_contains_MC_animation[i] = true; // Mark this block as containing animation
          shouldCopyMC = false;
          if (charactersCount < MAX_CHARACTERS)
          {
            charactersOnField[charactersCount] = CreateCharacter("MegaChonker", 350, 400, true, 0, 0.0);
            charactersPOS[charactersCount].x = targetPositions[i].x;
            charactersPOS[charactersCount].y = targetPositions[i].y;
            printf("Character %d position: %f, %f\n", charactersCount, charactersPOS[charactersCount].x, charactersPOS[charactersCount].y);
            charactersCount++;
          }
        }
        // Bomb
        else if (shouldCopyBomb && block_empty[i])
        {
          CopyImage(&imagePosition, targetPositions[i], Bomb1);
          shouldDrawAnimationLaika[i] = false;
          shouldDrawAnimationMC[i] = false;
          shouldDrawAnimationBomb[i] = true;
          shouldDrawAnimationFC[i] = false;
          brownColor_Bomb = LIGHTBROWN;
          block_empty[i] = false;
          block_contains_Bomb_animation[i] = true; // Mark this block as containing animation
          shouldCopyBomb = false;
          if (charactersCount < MAX_CHARACTERS)
          {
            charactersOnField[charactersCount] = CreateCharacter("Bomb", 400, 100, true, 200, 0.0);
            charactersPOS[charactersCount].x = targetPositions[i].x;
            charactersPOS[charactersCount].y = targetPositions[i].y;
            printf("Character %d position: %f, %f\n", charactersCount, charactersPOS[charactersCount].x, charactersPOS[charactersCount].y);
            charactersCount++;
          }
        }
        // FartCat
        else if (shouldCopyFC && block_empty[i])
        {
          CopyImage(&imagePosition, targetPositions[i], FartCat1);
          shouldDrawAnimationFC[i] = true;
          shouldDrawAnimationMC[i] = false;
          shouldDrawAnimationBomb[i] = false;
          shouldDrawAnimationBomb[i] = false;
          brownColor_FC = LIGHTBROWN;
          block_empty[i] = false;
          block_contains_FC_animation[i] = true; // Mark this block as containing animation
          shouldCopyFC = false;
          if (charactersCount < MAX_CHARACTERS)
          {
            charactersOnField[charactersCount] = CreateCharacter("FartCat", 300, 150, true, 100, 0.0);
            charactersPOS[charactersCount].x = targetPositions[i].x + 210;
            charactersPOS[charactersCount].y = targetPositions[i].y + 150;
            printf("Character %d position: %f, %f\n", charactersCount, charactersPOS[charactersCount].x, charactersPOS[charactersCount].y);
            charactersCount++;
          }
        }
        else if (block_contains_Laika_animation[i]) // Check if animation is present
        {
          shouldDrawAnimationLaika[i] = true; // Re-draw the animation
          shouldDrawAnimationMC[i] = false;
          shouldDrawAnimationBomb[i] = false;
          shouldDrawAnimationFC[i] = false;
        }
        else if (block_contains_MC_animation[i]) // Check if animation is present
        {
          shouldDrawAnimationLaika[i] = false; // Re-draw the animation
          shouldDrawAnimationMC[i] = true;
          shouldDrawAnimationBomb[i] = false;
          shouldDrawAnimationFC[i] = false;
        }
        else if (block_contains_Bomb_animation[i]) // Check if animation is present
        {
          shouldDrawAnimationLaika[i] = false;
          shouldDrawAnimationMC[i] = false;
          shouldDrawAnimationBomb[i] = true; // Re-draw the animation
          shouldDrawAnimationFC[i] = false;
        }
        else if (block_contains_FC_animation[i]) // Check if animation is present
        {
          shouldDrawAnimationLaika[i] = false;
          shouldDrawAnimationMC[i] = false;
          shouldDrawAnimationBomb[i] = false; // Re-draw the animation
          shouldDrawAnimationFC[i] = true;    // Re-draw the animation
        }
        else
        {
          shouldDrawAnimationLaika[i] = false;
          shouldDrawAnimationMC[i] = false;
          shouldDrawAnimationBomb[i] = false;
          shouldDrawAnimationFC[i] = false;
          shouldCopyLaika = false;
          shouldCopyMC = false;
          shouldCopyBomb = false;
          shouldCopyFC = false;
          brownColor_Laika = LIGHTBROWN;
          brownColor_MC = LIGHTBROWN;
          brownColor_Bomb = LIGHTBROWN;
          brownColor_FC = LIGHTBROWN;
        }
      }
    }
  }
}
// Define a timer variable
float fartCatAtkTimer = 0.0f;
float fartCatAtkInterval = 12.0f;

void DrawGame(void)
{
  float deltaTime = GetFrameTime();

  BeginDrawing();
  ClearBackground(RAYWHITE);

  // Draw the current frame
  DrawTexture(bg, get_center(bg).x, get_center(bg).y, WHITE);
  DrawTexture(bg_yard, get_center(bg_yard).x, get_center(bg_yard).y, (Color){0, 255, 0, 0});
  DrawTexture(score_board, 400, 0, WHITE);
  DrawText("Score:", 490, 30, 30, BLACK);

  DrawRectangle(0, 0, 250, 250, brownColor_Laika);
  DrawRectangle(0, 250, 250, 250, brownColor_MC);
  DrawRectangle(0, 500, 250, 250, brownColor_Bomb);
  DrawRectangle(0, 750, 250, 250, brownColor_FC);

  char priceBuffer[50];

  sprintf(priceBuffer, "%d", Laika.price);
  DrawText(priceBuffer, 115, 10, 30, WHITE);

  sprintf(priceBuffer, "%d", MegaChonker.price);
  DrawText(priceBuffer, 115, 260, 30, WHITE);

  sprintf(priceBuffer, "%d", Bomb.price);
  DrawText(priceBuffer, 115, 510, 30, WHITE);

  sprintf(priceBuffer, "%d", FartCat.price);
  DrawText(priceBuffer, 115, 760, 30, WHITE);

  int move = 0;

  for (int i = 0; i < NUM_BLOCKS; i++)
  {
    DrawRectangle(targetPositions[i].x, targetPositions[i].y, 250, 250, (Color){0, 255, 0, 0});

    if (shouldDrawAnimationLaika[i])
    {
      animation(LaikaFrames, currentFrame, frameTimer, Laika.name, targetPositions[i]);
    }

    if (shouldDrawAnimationMC[i])
    {
      animation(MegaChonkerFrames, currentFrame, frameTimer, MegaChonker.name, targetPositions[i]);
    }

    if (shouldDrawAnimationBomb[i])
    {
      animation(BombFrames, currentFrame, frameTimer, Bomb.name, targetPositions[i]);
    }

    if (shouldDrawAnimationFC[i])
    {
      animation(FartCatFrames, currentFrame, frameTimer, FartCat.name, targetPositions[i]);
    }
    // Draw FartCatAtk here, outside the for loop
    for (int i = 0; i < NUM_BLOCKS; i++)
    {
      if (shouldDrawAnimationFC[i])
      {
        // Check the timer to display FartCatAtk
        fartCatAtkTimer += GetFrameTime();

        if (fartCatAtkTimer >= fartCatAtkInterval)
        {
          DrawTexture(FartCatAtk, targetPositions[i].x + 220 + move, targetPositions[i].y + 100, WHITE);
          fartCatAtkTimer = 0.0f; // Reset the timer
        }
        // move += 10;
      }
    }
    DrawTexture(Laika1, 0, 0, WHITE);
    DrawTexture(MegaChonker1, 0, 250, WHITE);
    DrawTexture(Bomb1, 0, 500, WHITE);
    DrawTexture(FartCat1, 0, 750, WHITE);

    ufoSpawnTimer += deltaTime;

    // Generate a new UFO if the spawn timer exceeds the interval
    if (ufoSpawnTimer >= ufoSpawnInterval)
    {
      for (int i = 0; i < MAX_MONSTERS; i++)
      {
        if (!ufos[i].active)
        {
          CreateMonsterCharacter(&ufos[i], "ufo", 350, true, 120, 1.15);
          ufoSpawnTimer = 0.0f; // Reset the spawn timer
          break;                // Break out of the loop after spawning one UFO
        }
      }
    }

    // Update and draw active UFOs
    for (int i = 0; i < MAX_MONSTERS; i++)
    {
      if (ufos[i].active)
      {
        UpdateMonsters(&ufos[i], deltaTime);
        animation(UfoFrames, currentFrame, frameTimer, Ufo.name, ufos[i].position);
      }
    }

    // Draw the projectiles
    for (int i = 0; i < MAX_PROJECTILES; i++)
    {
      if (laikaProjectiles[i].active)
      {
        // DrawTexture(LaikaAtkTexture, laikaProjectiles[i].position.x, laikaProjectiles[i].position.y, WHITE);
        DrawRectangle(laikaProjectiles[i].position.x, laikaProjectiles[i].position.y, 40, 10, BLUE);
      }
    }
  }

  EndDrawing();
}

void UnloadGame(void)
{
  // Unload textures
  for (int i = 0; i < 3; i++)
  {
    UnloadTexture(LaikaFrames[i]);
    UnloadTexture(MegaChonkerFrames[i]);
    UnloadTexture(BombFrames[i]);
    UnloadTexture(FartCatFrames[i]);
  }
  UnloadTexture(bg);
  UnloadTexture(bg_yard);
  UnloadTexture(score_board);
  UnloadTexture(Laika1);
  UnloadTexture(MegaChonker1);
  UnloadTexture(Bomb1);
  UnloadTexture(FartCat1);
  UnloadTexture(FartCatAtk);

  CloseWindow();
}
