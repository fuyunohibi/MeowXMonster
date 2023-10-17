#include <stdio.h>
#include <string.h>
#include "../../include/raylib.h"
#include "../../include/raymath.h"
#include "constant/game_data.h"
#include "constant/game_functions.h"
#include "character/character.h"

extern int findRow(int i);  //line 55

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

MonsterCharacter CreateMonsterCharacter(MonsterCharacter *monster, const char *name, int HP, int attackDamage, float attackPerSecond)
{
  strncpy(monster->name, name, sizeof(monster->name));
  monster->attackDamage = attackDamage;
  monster->attackPerSecond = attackPerSecond;
  monster->animationTimer = 0.0f;
  monster->HP = HP;
  int randomIndex = GetRandomValue(0, 2);    // Randomly choose an index from 0 to 2
  monster->position = initPosition[randomIndex]; // Use the selected position
  monster->active = true;
  monster->isAlive = true;
  monster->animationTimer = 0.0f;
  monster->row = randomIndex;
}

// int findRow(int i) {
//   while(i > 2)
//   {
//     i -= 3;
//   }

//   return i;
// }

void UpdateMonsters(MonsterCharacter *monster, float deltaTime, int speed, Texture2D monsterFrames[NUM_FRAMES])
{
  for (int i = 0; i < charactersCount; i++)
  {
    if (monster->position.x <= charactersPOS[i].x && monster->row == charactersRow[i] && monster->isAlive)
    {
      charactersOnField[i].HP -= monster->attackDamage;
      printf("Character %d HP: %d\n", i, charactersOnField[i].HP);
      if (charactersOnField[i].HP <= 0)
      {
        charactersOnField[i].isAlive = false;
      }

      monster->active = false;
      monster->isAlive = false;

      score += 1;
    }
  }

  for (int i = 0; i < MAX_PROJECTILES; i++)
  {
    if (laikaProjectiles[i].active)
    {
      if (laikaProjectiles[i].position.y == 296 && laikaProjectiles[i].position.x >= monster->position.x && monster->row == 0)
      {
        laikaProjectiles[i].active = false;
        monster->HP -= Laika.attackDamage;
      }
      else if (laikaProjectiles[i].position.y == 546 && laikaProjectiles[i].position.x >= monster->position.x && monster->row == 1)
      {
        laikaProjectiles[i].active = false;
        monster->HP -= Laika.attackDamage;
      }
      else if (laikaProjectiles[i].position.y == 796 && laikaProjectiles[i].position.x >= monster->position.x && monster->row == 2)
      {
        laikaProjectiles[i].active = false;
        monster->HP -= Laika.attackDamage;
      }
    }
  }
  if (monster->HP <= 0)
  {
    monster->active = false;
    monster->isAlive = false;
  }

  if(monster->isAlive){
    monster->position.x -= speed * deltaTime;
  } // Move monster to the left

  if (monster->position.x < 250)
  {
    // monster->active = false; // Deactivate monster when it goes off-screen
    UnloadGame(); // Game over when monster walk through column 1 (x = 250), Change UnloadGame() to function GameOver()
  }

  // Update any other monster-related logic here
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
      laikaProjectiles[j].speed = 3.0f;
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
  char MuscleName[50];

  strcpy(LaikaName, Laika.name);
  strcpy(MegaChonkerName, MegaChonker.name);
  strcpy(BombName, Bomb.name);
  strcpy(FartCatName, FartCat.name);
  strcpy(ufoName, Ufo.name);
  strcpy(MuscleName, Muscle.name);

  load_animation(LaikaFrames, Laika.name);
  load_animation(MegaChonkerFrames, MegaChonker.name);
  load_animation(BombFrames, Bomb.name);
  load_animation(FartCatFrames, FartCat.name);
  load_animation_monster(JellyFrames, "jelly");
  load_animation_monster(UfoFrames, "ufo");
  load_animation_monster(MuscleFrames, "muscle");
  load_animation_monster(LonglegFrames, "LongLeg");

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
      // printf("%f, %f", laikaProjectiles[i].direction.x, laikaProjectiles[i].speed);
    
      // Check if projectile is out of bounds
      if (laikaProjectiles[i].position.x > SCREEN_WIDTH || laikaProjectiles[i].position.x < 0 ||
          laikaProjectiles[i].position.y > SCREEN_HEIGHT || laikaProjectiles[i].position.y < 0)
      {
        laikaProjectiles[i].active = false;
      }

      // if (laikaProjectiles[i].position.y > 0 && laikaProjectiles[i].position.y < 310)
      // {
      //   for (int j = 0; j < MAX_MONSTERS; j++)
      //   {
      //     if ((laikaProjectiles[i].position.x >= jellys[j].position.x && jellys[j].row == 0) || 
      //         (laikaProjectiles[i].position.x >= ufos[j].position.x && ufos[j].row == 0) ||
      //         (laikaProjectiles[i].position.x >= muscles[j].position.x && muscles[j].row == 0) || 
      //         (laikaProjectiles[i].position.x >= longlegs[j].position.x && longlegs[j].row == 0))
      //     {
      //       laikaProjectiles[i].active = false;
      //       printf("%f, %f\n", laikaProjectiles[i].position.x, jellys[j].position.x);
      //       printf("%f, %f\n", laikaProjectiles[i].position.x, ufos[j].position.x);
      //       printf("%f, %f\n", laikaProjectiles[i].position.x, muscles[j].position.x);
      //       printf("%f, %f\n", laikaProjectiles[i].position.x, longlegs[j].position.x);
      //     }
      //   }
      // }
      // else if (laikaProjectiles[i].position.y >= 310 && laikaProjectiles[i].position.y < 560)
      // {
      //   for (int j = 0; j < monsterRow2Size; j++)
      //   {
      //     if (laikaProjectiles[i].position.x >= monsterRow2[j].position.x)
      //     {
      //       laikaProjectiles[i].active = false;
      //       printf("%f, %f\n", laikaProjectiles[i].position.x, monsterRow2[j].position.x);
      //     }
      //   }
      // }
      // else if (laikaProjectiles[i].position.y >= 560 && laikaProjectiles[i].position.y < 810)
      // {
      //   for (int j = 0; j < monsterRow3Size; j++)
      //   {
      //     if (laikaProjectiles[i].position.x >= monsterRow3[j].position.x)
      //     {
      //       laikaProjectiles[i].active = false;
      //       printf("%f, %f\n", laikaProjectiles[i].position.x, monsterRow3[j].position.x);
      //     }
      //   }
      // }
      // 296 546 796
      // if(laikaProjectiles[i].position.y > 0 && laikaProjectiles[i].position.y < 310){
      //   for(int j = 0 ;j < monsterRow1Size; j++){
      //     if(laikaProjectiles[i].position.x >= monsterRow1[j].position.x){
      //       laikaProjectiles[i].active = false;
      //       printf("%f, %f\n", laikaProjectiles[i].position.x, monsterRow1[j].position.x);
      //     }
      //   }
      // }
      // else if(laikaProjectiles[i].position.y >= 310 && laikaProjectiles[i].position.y < 560){
      //   for (int j = 0; j < monsterRow2Size; j++)
      //   {
      //     if (laikaProjectiles[i].position.x >= monsterRow2[j].position.x)
      //     {
      //       laikaProjectiles[i].active = false;
      //       printf("%f, %f\n", laikaProjectiles[i].position.x, monsterRow2[j].position.x);
      //     }
      //   }
      // }
      // else if(laikaProjectiles[i].position.y >= 560 && laikaProjectiles[i].position.y < 810){
      //   for (int j = 0; j < monsterRow3Size; j++)
      //   {
      //     if (laikaProjectiles[i].position.x >= monsterRow3[j].position.x)
      //     {
      //       laikaProjectiles[i].active = false;
      //       printf("%f, %f\n", laikaProjectiles[i].position.x, monsterRow3[j].position.x);
      //     }
      //   }
      // }
      
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
            charactersOnField[charactersCount] = CreateCharacter(Laika.name, Laika.price, Laika.HP, true, Laika.attackDamage, Laika.attackPerSecond);
            charactersPOS[charactersCount].x = targetPositions[i].x + 210;
            charactersPOS[charactersCount].y = targetPositions[i].y + 130;
            charactersRow[charactersCount] = findRow(i);
            printf("Character %d position: %f, %f Row: %d\n", charactersCount, charactersPOS[charactersCount].x, charactersPOS[charactersCount].y, charactersRow[charactersCount]);
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
            charactersOnField[charactersCount] = CreateCharacter(MegaChonker.name, MegaChonker.price, MegaChonker.HP, true, MegaChonker.attackDamage, MegaChonker.attackPerSecond);
            charactersPOS[charactersCount].x = targetPositions[i].x;
            charactersPOS[charactersCount].y = targetPositions[i].y;
            charactersRow[charactersCount] = findRow(i);
            printf("Character %d position: %f, %f Row: %d\n", charactersCount, charactersPOS[charactersCount].x, charactersPOS[charactersCount].y, charactersRow[charactersCount]);
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
            charactersOnField[charactersCount] = CreateCharacter(Bomb.name, Bomb.price, Bomb.HP, true, Bomb.attackDamage, Bomb.attackPerSecond);
            charactersPOS[charactersCount].x = targetPositions[i].x;
            charactersPOS[charactersCount].y = targetPositions[i].y;
            charactersRow[charactersCount] = findRow(i);
            printf("Character %d position: %f, %f Row: %d\n", charactersCount, charactersPOS[charactersCount].x, charactersPOS[charactersCount].y, charactersRow[charactersCount]);
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
            charactersOnField[charactersCount] = CreateCharacter(FartCat.name, FartCat.price, FartCat.HP, true, FartCat.attackDamage, FartCat.attackPerSecond);
            charactersPOS[charactersCount].x = targetPositions[i].x + 210;
            charactersPOS[charactersCount].y = targetPositions[i].y + 150;
            charactersRow[charactersCount] = findRow(i);
            printf("Character %d position: %f, %f Row: %d\n", charactersCount, charactersPOS[charactersCount].x, charactersPOS[charactersCount].y, charactersRow[charactersCount]);
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
float fartCatAtkInterval = 20.0f;

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
  sprintf(scoreBuffer, "%d", score);
  DrawText(scoreBuffer, 530, 80, 30, BLACK);

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

    monsterSpawnTimer += deltaTime;

    // Generate a new UFO if the spawn timer exceeds the interval
    if (monsterSpawnTimer >= monsterSpawnInterval)
    {
      int randomIndex = GetRandomValue(0, 3); // Use random_number from asm for random with probability
      for (int i = 0; i < MAX_MONSTERS; i++)
      {
        if (!jellys[i].active && randomIndex == 0)
        {
          CreateMonsterCharacter(&jellys[i], "jelly", 350, 120, 1.15);
          monsterSpawnTimer = 0.0f; // Reset the spawn timer
          break;
        }
        else if (!ufos[i].active && randomIndex == 1)
        {
          CreateMonsterCharacter(&ufos[i], "ufo", 350, 120, 1.15);
          monsterSpawnTimer = 0.0f; // Reset the spawn timer
          break;
        }
        else if (!muscles[i].active && randomIndex == 2)
        {
          CreateMonsterCharacter(&muscles[i], "muscle", 350, 120, 1.15);
          monsterSpawnTimer = 0.0f; // Reset the spawn timer
          break;
        }
        else if (!longlegs[i].active && randomIndex == 3)
        {
          CreateMonsterCharacter(&longlegs[i], "longlegs", 350, 120, 1.15);
          monsterSpawnTimer = 0.0f; // Reset the spawn timer
          break;
        }
      }
    }

    // Update and draw active UFOs
    for (int i = 0; i < MAX_MONSTERS; i++)
    {
      if (jellys[i].active)
      {
        UpdateMonsters(&jellys[i], deltaTime, Jelly.walkSpeed, JellyFrames);
        if (jellys[i].isAlive)
        {
          animation(JellyFrames, currentFrame, frameTimer, Jelly.name, jellys[i].position);
        }
      }
      if (ufos[i].active)
      {
        UpdateMonsters(&ufos[i], deltaTime, Ufo.walkSpeed, UfoFrames);
        if (ufos[i].isAlive)
        {
          animation(UfoFrames, currentFrame, frameTimer, Ufo.name, ufos[i].position);
        }
      }
      if (muscles[i].active)
      {
        UpdateMonsters(&muscles[i], deltaTime, Muscle.walkSpeed, MuscleFrames);
        if (muscles[i].isAlive)
        {
          animation(MuscleFrames, currentFrame, frameTimer, Muscle.name, muscles[i].position);
        }
      }
      if (longlegs[i].active)
      {
        UpdateMonsters(&longlegs[i], deltaTime, Longleg.walkSpeed, LonglegFrames);
        if (longlegs[i].isAlive)
        {
          animation(LonglegFrames, currentFrame, frameTimer, Longleg.name, longlegs[i].position);
        }
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