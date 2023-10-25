#include <stdio.h>
#include <string.h>
#include "constant/game_data.h"
#include "constant/game_constants.h"
#include "constant/game_functions.h"
#include "character/character.h"
#include <stdlib.h>
#include <time.h>

extern int findRow(int i);
extern int random_number(int random, int max);
extern int calculate_center(int screen, int length);
extern double* create_character(int index);
extern double* create_monster(int index);
extern int GameOverPage(void);
extern int add_function(int score, int adder);
extern int set_total_score(int score);
extern int get_total_score(void);

int get_random(int max) {
  srand(time(NULL));
  int r = rand();
  int result = random_number(r,max);
  return result;
}

Character CreateCharacter(int index, int blockPosition){
  Character newCharacter;
  double* characterArray = create_character(index);
  newCharacter.name = (float)(characterArray[0]);
  newCharacter.price = (float)(characterArray[1]);
  newCharacter.HP = (float)(characterArray[2]);
  newCharacter.isAlive = true;
  newCharacter.attackDamage = (float)(characterArray[4]);
  newCharacter.attackPerSecond = (float)(characterArray[5]);
  newCharacter.rightBoundery = (float)(characterArray[6]);
  newCharacter.attackTimer = (float)(characterArray[7]);
  newCharacter.blockPosition = blockPosition;
  return newCharacter;
}

MonsterCharacter CreateMonsterCharacter(MonsterCharacter *monster, int index){
  double* monsterArray = create_monster(index);
  monster->name = (float)(monsterArray[0]);
  monster->killReward = (float)(monsterArray[1]);
  monster->HP = (float)(monsterArray[2]);
  monster->attackDamage = (float)(monsterArray[4]);
  monster->attackPerSecond = (float)(monsterArray[5]);
  int randomRow = GetRandomValue(0, 2);   // Randomly choose an index from 0 to 2
  monster->position = initPosition[randomRow]; // Use the selected position
  monster->active = true;
  monster->isAlive = true;
  monster->row = randomRow;
}

void UpdateMonsters(MonsterCharacter *monster, float deltaTime, int speed){
  for (int i = 0; i < charactersCount; i++)  {
    float characterRightBoundary = charactersPOS[i].x + charactersOnField[i].rightBoundery;
    float characterLeftBoundary = charactersPOS[i].x - 10.0;
    if (monster->position.x >= characterLeftBoundary && monster->position.x <= characterRightBoundary && monster->row == charactersRow[i] && monster->isAlive && charactersOnField[i].isAlive){
      monster->position.x = characterRightBoundary;
      if(charactersOnField[i].name == 4.0) /*Bomb do AOE damage */{
        monster->HP -= charactersOnField[i].attackDamage;
        for(int j = 0; j < MAX_MONSTERS; j++){
          if (jellys[j].position.x >= characterLeftBoundary && jellys[j].position.x <= characterRightBoundary && abs(jellys[j].row - charactersRow[i]) <= 1){
            jellys[j].HP -= charactersOnField[i].attackDamage;
          }
          if (ufos[j].position.x >= characterLeftBoundary && ufos[j].position.x <= characterRightBoundary && abs(ufos[j].row - charactersRow[i]) <= 1){
            ufos[j].HP -= charactersOnField[i].attackDamage;
          }
          if (muscles[j].position.x >= characterLeftBoundary && muscles[j].position.x <= characterRightBoundary && abs(muscles[j].row - charactersRow[i]) <= 1){
            muscles[j].HP -= charactersOnField[i].attackDamage;
          }
        }
        bombExplosions[i].active = true;
        bombExplosions[i].position = charactersPOS[i];
      }
      charactersOnField[i].HP -= monster->attackDamage;
      if (charactersOnField[i].HP <= 0){
        int blockPosition = charactersOnField[i].blockPosition;
        charactersOnField[i].isAlive = false;
        shouldDrawAnimationLaika[blockPosition] = false;
        shouldDrawAnimationBomb[blockPosition] = false;
        shouldDrawAnimationMC[blockPosition] = false;
        block_contains_Laika_animation[blockPosition] = false;
        block_contains_Bomb_animation[blockPosition] = false;
        block_contains_MC_animation[blockPosition] = false;
        block_empty[blockPosition] = true;
      }
      break;
    }
  }

  for (int i = 0; i < MAX_PROJECTILES; i++){
    if (laikaProjectiles[i].active){
      if (laikaProjectiles[i].position.y == 296 && laikaProjectiles[i].position.x >= monster->position.x && monster->row == 0){
        laikaProjectiles[i].active = false;
        monster->HP -= Laika.attackDamage;
      } else if (laikaProjectiles[i].position.y == 546 && laikaProjectiles[i].position.x >= monster->position.x && monster->row == 1){
        laikaProjectiles[i].active = false;
        monster->HP -= Laika.attackDamage;
      } else if (laikaProjectiles[i].position.y == 796 && laikaProjectiles[i].position.x >= monster->position.x && monster->row == 2){
        laikaProjectiles[i].active = false;
        monster->HP -= Laika.attackDamage;
      }
    }
  }

  if (monster->HP <= 0){
    monster->isAlive = false;
    monster->active = false;
    score = set_total_score(add_function(score,1));
    money += monster->killReward;
  }
  if(monster->isAlive){
    monster->position.x -= speed * deltaTime; // Move monster to the left
  }
  if (monster->position.x < 250){
    UnloadGame(); // Game over when monster walk through column 1 (x = 250), Change UnloadGame() to function GameOver()
    GameOverPage();
  }
}

int start_game(void){
  InitializeGame();
  while (!WindowShouldClose()) {
    UpdateGame();
    DrawGame();
  }
  UnloadGame();

  return 0;
}

void shootProjectileFromCharacter(Character character, Vector2 position){
  for (int j = 0; j < MAX_PROJECTILES; j++) {
    if (!laikaProjectiles[j].active){
      laikaProjectiles[j].position.x = position.x + 210; // Starting position of the projectile
      laikaProjectiles[j].position.y = position.y + 130;
      laikaProjectiles[j].direction = (Vector2){1, 0}; // Shoots to the right, modify if needed
      laikaProjectiles[j].speed = 3.0f;
      laikaProjectiles[j].active = true;
      break;
    }
  }
}

Vector2 get_center(Texture2D texture){
  Vector2 center;
  center.x = (float)calculate_center(SCREEN_WIDTH, texture.width);
  center.y = (float)calculate_center(SCREEN_HEIGHT, texture.height);
  return center;
}

void animation(Texture2D frames[NUM_FRAMES], int currentFrame, Vector2 position){
  DrawTexture(frames[currentFrame], position.x, position.y, WHITE);
}

void load_animation(Texture2D frames[NUM_FRAMES], const char *name){
  char filename[256];
  for (int i = 0; i < NUM_FRAMES; i++){
    sprintf(filename, "../assets/images/avatar/%s/%s%d.png", name, name, i + 1);
    frames[i] = LoadTexture(filename);
  }
}

void load_animation_monster(Texture2D frames[NUM_FRAMES], const char *name){
  char filename[256];
  for (int i = 0; i < NUM_FRAMES; i++){
    sprintf(filename, "../assets/images/monster/%s/%s%d.png", name, name, i + 1);
    frames[i] = LoadTexture(filename);
  }
}

void load_animation_explode(Texture2D frames[NUM_FRAMES]){
  char filename[256];
  for (int i = 0; i < NUM_FRAMES; i++)  {
    sprintf(filename, "../assets/images/avatar/Bomb/Atk/BombExplode%d.png", i + 1);
    frames[i] = LoadTexture(filename);
  }
}

bool IsMouseOverBox(Vector2 mousePosition, Vector2 boxPosition, Texture2D Box){
  return CheckCollisionPointRec(mousePosition, (Rectangle){boxPosition.x, boxPosition.y, Box.width, Box.height});
}

void CopyImage(Vector2 *imagePosition, Vector2 targetPosition, Texture2D image){
  *imagePosition = targetPosition;
}

void InitializeGame(void){
  score = 0;
  money = 200;
  monsterCount = 0;
  shouldCopyLaika = false;
  shouldCopyMC = false;
  shouldCopyBomb = false;
  for (int i = 0; i < MAX_PROJECTILES; i++)  {
    laikaProjectiles[i].active = false;
  }
  for(int i = 0; i < MAX_CHARACTERS; i++)  {
    bombExplosions[i].active = false;
    bombExplosions[i].currentFrame = 0;
  }
  for(int i = 0; i < MAX_CHARACTERS; i++)  {
    shouldDrawAnimationLaika[i] = false;
    shouldDrawAnimationMC[i] = false;
    shouldDrawAnimationBomb[i] = false;
    charactersOnField[i].isAlive = false;
  }
  for(int i = 0; i < MAX_MONSTERS; i++)  {
    jellys[i].active = false;
    ufos[i].active = false;
    muscles[i].active = false;
  }
  SetTargetFPS(60);
  // Initialize character
  load_animation(LaikaFrames, "Laika");
  load_animation(MegaChonkerFrames, "MegaChonker");
  load_animation(BombFrames, "Bomb");
  load_animation_monster(JellyFrames, "Jelly");
  load_animation_monster(UfoFrames, "Ufo");
  load_animation_monster(MuscleFrames, "Muscle");
  load_animation_explode(ExplodeFrames);

  // Load background and character textures
  bg = LoadTexture("../assets/images/background/background.PNG");
  bg_yard = LoadTexture("../assets/images/background/yard.png");
  score_board = LoadTexture("../assets/images/background/Score.png");
  Laika1 = LoadTexture("../assets/images/avatar/Laika/Laika1.png");
  MegaChonker1 = LoadTexture("../assets/images/avatar/MegaChonker/MegaChonker1.png");
  Bomb1 = LoadTexture("../assets/images/avatar/Bomb/Bomb1.png");

  Vector2 blockStart = get_center(bg_yard);
  for (int i = 0; i < NUM_BLOCKS; i++)  {
    int col = i / 3; // Columns (0 to 4)
    int row = i % 3; // Rows (0 to 2)
    targetPositions[i] = (Vector2){blockStart.x + (col * 250), blockStart.y + (row * 250)};
    block_empty[i] = true;
    block_contains_Laika_animation[i] = false;
    block_contains_MC_animation[i] = false;
    block_contains_Bomb_animation[i] = false;
  }
  // Set initial positions
  targetPosition = get_center(bg_yard);
  targetPosition2 = (Vector2){get_center(bg_yard).x, get_center(bg_yard).y + 250};
}

void UpdateGame(void){
  // Update animation frame
  frameTimer += GetFrameTime();
  if (frameTimer >= frameSpeed)  {
    frameTimer = 0;
    currentFrame = (currentFrame + 1) % 3; // Cycle through frames
  }
  static double moneyTimer = 0;
  moneyTimer += GetFrameTime();
  if (moneyTimer >= 3.0) /* Increase money every 3 seconds */  {
    money = add_function(money, 30); // Increase money by 100
    moneyTimer = 0;
  }
  if(score >= MAX_MONSTERS){
    UnloadGame();
    GameOverPage();
  }

  for (int i = 0; i < MAX_PROJECTILES; i++)  {
    if (laikaProjectiles[i].active)    {
      laikaProjectiles[i].position.x += laikaProjectiles[i].direction.x * laikaProjectiles[i].speed;
      laikaProjectiles[i].position.y += laikaProjectiles[i].direction.y * laikaProjectiles[i].speed;
    
      if (laikaProjectiles[i].position.x > SCREEN_WIDTH || laikaProjectiles[i].position.x < 0 ||
          laikaProjectiles[i].position.y > SCREEN_HEIGHT || laikaProjectiles[i].position.y < 0)      {
        laikaProjectiles[i].active = false;
      }
    }
  }

  for (int i = 0; i < charactersCount; i++) {
    if (charactersOnField[i].name == 1) {
      charactersOnField[i].attackTimer += GetFrameTime();

      float timeBetweenShots = 1.0f / charactersOnField[i].attackPerSecond;

      if (charactersOnField[i].attackTimer >= timeBetweenShots && charactersOnField[i].isAlive)   {
        charactersOnField[i].attackTimer = 0.0f; // Reset timer
        shootProjectileFromCharacter(charactersOnField[i], charactersPOS[i]);
      }
    }
  }

  Vector2 mousePosition = GetMousePosition();

  if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))  {
    for (int i = 0; i < NUM_BLOCKS; i++)    {
      if (IsMouseOverBox(mousePosition, (Vector2){0, 0}, Laika1)) {
        shouldCopyLaika = true;
        shouldCopyMC = false;
        shouldCopyBomb = false;
        brownColor_Laika = darkbrown;
        brownColor_MC = LIGHTBROWN;
        brownColor_Bomb = LIGHTBROWN;
      } else if (IsMouseOverBox(mousePosition, (Vector2){0, 250}, MegaChonker1))   {
        shouldCopyLaika = false;
        shouldCopyMC = true;
        shouldCopyBomb = false;
        brownColor_Laika = LIGHTBROWN;
        brownColor_MC = darkbrown;
        brownColor_Bomb = LIGHTBROWN;
      } else if (IsMouseOverBox(mousePosition, (Vector2){0, 500}, Bomb1))   {
        shouldCopyLaika = false;
        shouldCopyMC = false;
        shouldCopyBomb = true;
        brownColor_Laika = LIGHTBROWN;
        brownColor_MC = LIGHTBROWN;
        brownColor_Bomb = darkbrown;
      } else if (CheckCollisionPointRec(mousePosition, (Rectangle){targetPositions[i].x, targetPositions[i].y, 250, 250})) {
        if (shouldCopyLaika && block_empty[i] && charactersCount < MAX_CHARACTERS && money >= Laika.price){
          CopyImage(&imagePosition, targetPositions[i], Laika1);
          shouldDrawAnimationLaika[i] = true;
          shouldDrawAnimationMC[i] = false;
          shouldDrawAnimationBomb[i] = false;
          brownColor_Laika = LIGHTBROWN;
          block_empty[i] = false;
          block_contains_Laika_animation[i] = true; // Mark this block as containing animation
          shouldCopyLaika = false;
          money -= Laika.price;
          charactersOnField[charactersCount] = CreateCharacter(1, i);
          charactersPOS[charactersCount].x = targetPositions[i].x;
          charactersPOS[charactersCount].y = targetPositions[i].y;
          charactersRow[charactersCount] = findRow(i);
          charactersCount++;
        } else if (shouldCopyMC && block_empty[i] && charactersCount < MAX_CHARACTERS && money >= MegaChonker.price) {
          CopyImage(&imagePosition, targetPositions[i], MegaChonker1);
          shouldDrawAnimationLaika[i] = false;
          shouldDrawAnimationMC[i] = true;
          shouldDrawAnimationBomb[i] = false;
          brownColor_MC = LIGHTBROWN;
          block_empty[i] = false;
          block_contains_MC_animation[i] = true; // Mark this block as containing animation
          shouldCopyMC = false;
          money -= MegaChonker.price;
          charactersOnField[charactersCount] = CreateCharacter(3, i);
          charactersPOS[charactersCount].x = targetPositions[i].x;
          charactersPOS[charactersCount].y = targetPositions[i].y;
          charactersRow[charactersCount] = findRow(i);
          charactersCount++;
        } else if (shouldCopyBomb && block_empty[i] && charactersCount < MAX_CHARACTERS && money >= Bomb.price){
          CopyImage(&imagePosition, targetPositions[i], Bomb1);
          shouldDrawAnimationLaika[i] = false;
          shouldDrawAnimationMC[i] = false;
          shouldDrawAnimationBomb[i] = true;
          brownColor_Bomb = LIGHTBROWN;
          block_empty[i] = false;
          block_contains_Bomb_animation[i] = true; // Mark this block as containing animation
          shouldCopyBomb = false;
          money -= Bomb.price;
          charactersOnField[charactersCount] = CreateCharacter(4, i);
          charactersPOS[charactersCount].x = targetPositions[i].x;
          charactersPOS[charactersCount].y = targetPositions[i].y;
          charactersRow[charactersCount] = findRow(i);
          charactersCount++;
        } else if (block_contains_Laika_animation[i]) /* Check if animation is present */ {
          shouldDrawAnimationLaika[i] = true; // Re-draw the animation
          shouldDrawAnimationMC[i] = false;
          shouldDrawAnimationBomb[i] = false;
        } else if (block_contains_MC_animation[i]) /*Check if animation is present */ {
          shouldDrawAnimationLaika[i] = false; // Re-draw the animation
          shouldDrawAnimationMC[i] = true;
          shouldDrawAnimationBomb[i] = false;
        } else if (block_contains_Bomb_animation[i]) {  // Check if animation is present
          shouldDrawAnimationLaika[i] = false;
          shouldDrawAnimationMC[i] = false;
          shouldDrawAnimationBomb[i] = true; // Re-draw the animation
        } else {
          shouldDrawAnimationLaika[i] = false;
          shouldDrawAnimationMC[i] = false;
          shouldDrawAnimationBomb[i] = false;
          shouldCopyLaika = false;
          shouldCopyMC = false;
          shouldCopyBomb = false;
          brownColor_Laika = LIGHTBROWN;
          brownColor_MC = LIGHTBROWN;
          brownColor_Bomb = LIGHTBROWN;
        }
      }
    }
  }
}

void DrawGame(void) {
  float deltaTime = GetFrameTime();
  char priceBuffer[50];
  int randomIndex; // Use random_number from asm for random with probability
  BeginDrawing();
  ClearBackground(RAYWHITE);
  DrawTexture(bg, get_center(bg).x, get_center(bg).y, WHITE);  // Draw the current frame
  DrawTexture(bg_yard, get_center(bg_yard).x, get_center(bg_yard).y, (Color){0, 255, 0, 0});
  DrawTexture(score_board, 400, 0, WHITE);
  DrawText("Score:", 490, 30, 30, BLACK);
  sprintf(scoreBuffer, "%d", score);
  DrawText(scoreBuffer, 530, 80, 30, BLACK);
  DrawText("Money:", 750, 30, 30, BLACK);
  sprintf(moneyBuffer, "%d", money);
  DrawText(moneyBuffer, 790, 80, 30, BLACK);
  DrawRectangle(0, 0, 250, 250, brownColor_Laika);
  DrawRectangle(0, 250, 250, 250, brownColor_MC);
  DrawRectangle(0, 500, 250, 250, brownColor_Bomb);
  sprintf(priceBuffer, "%.0f", Laika.price);
  DrawText(priceBuffer, 115, 10, 30, WHITE);
  sprintf(priceBuffer, "%.0f", MegaChonker.price);
  DrawText(priceBuffer, 115, 260, 30, WHITE);
  sprintf(priceBuffer, "%.0f", Bomb.price);
  DrawText(priceBuffer, 115, 510, 30, WHITE);

  for (int i = 0; i < NUM_BLOCKS; i++) {
    DrawRectangle(targetPositions[i].x, targetPositions[i].y, 250, 250, (Color){0, 255, 0, 0});
    if (shouldDrawAnimationLaika[i]) {
      animation(LaikaFrames, currentFrame, targetPositions[i]);
    }
    if (shouldDrawAnimationMC[i]) {
      animation(MegaChonkerFrames, currentFrame, targetPositions[i]);
    }
    if (shouldDrawAnimationBomb[i]) {
      animation(BombFrames, currentFrame, targetPositions[i]);
    }
    for (int i = 0; i < MAX_PROJECTILES; i++) { // Draw the projectiles
      if (laikaProjectiles[i].active) {
        DrawRectangle(laikaProjectiles[i].position.x, laikaProjectiles[i].position.y, 40, 10, BLUE);
      }
    }
    DrawTexture(Laika1, 0, 0, WHITE);
    DrawTexture(MegaChonker1, 0, 250, WHITE);
    DrawTexture(Bomb1, 0, 500, WHITE);
    monsterSpawnTimer += deltaTime;
    
    if(monsterCount < 10) {
      randomIndex = get_random(1);
      monsterSpawnInterval = 70.0f;
    } else if(monsterCount < 20) {
      randomIndex = get_random(2);
      monsterSpawnInterval = 45.0f;
    } else if(monsterCount < 30) {
      randomIndex = get_random(2);
      monsterSpawnInterval = 30.0f;
    } else {
      randomIndex = get_random(2);
      monsterSpawnInterval = 15.0f;
    }

    if (monsterSpawnTimer >= monsterSpawnInterval && monsterCount <= MAX_MONSTERS) { // Generate a new monster if the spawn timer exceeds the interval
      for (int i = 0; i < MAX_MONSTERS; i++) {
        if (!jellys[i].active && randomIndex == 0) {
          CreateMonsterCharacter(&jellys[i], 1);
          monsterSpawnTimer = 0.0f; // Reset the spawn timer
          monsterCount++;
          // printf("monster: %d, row: %d\n", jellys[i].name, jellys[i].row);
          break;
        } else if (!ufos[i].active && randomIndex == 1) {
          CreateMonsterCharacter(&ufos[i], 2);
          // printf("monster: %d, row: %d\n", ufos[i].name, ufos[i].row);
          monsterSpawnTimer = 0.0f; // Reset the spawn timer
          monsterCount++;
          break;
        } else if (!muscles[i].active && randomIndex == 2) {
          CreateMonsterCharacter(&muscles[i], 3);
          // printf("monster: %d, row: %d\n", muscles[i].name, muscles[i].row);
          monsterSpawnTimer = 0.0f; // Reset the spawn timer
          monsterCount++;
          break;
        }
      }
    }

    for (int i = 0; i < monsterCount; i++) { // Update and draw active monsters
      if (jellys[i].active) {
        UpdateMonsters(&jellys[i], deltaTime, Jelly.walkSpeed);
        if (jellys[i].isAlive) {
          animation(JellyFrames, currentFrame, jellys[i].position);
        }
      }
      if (ufos[i].active) {
        UpdateMonsters(&ufos[i], deltaTime, Ufo.walkSpeed);
        if (ufos[i].isAlive) {
          animation(UfoFrames, currentFrame, ufos[i].position);
        }
      }
      if (muscles[i].active) {
        UpdateMonsters(&muscles[i], deltaTime, Muscle.walkSpeed);
        if (muscles[i].isAlive) {
          animation(MuscleFrames, currentFrame, muscles[i].position);
        }
      }
    }
  }

  for(int i = 0; i < charactersCount; i++) {
    if (bombExplosions[i].active) {
      if (bombExplosions[i].currentFrame >= 2) {
        bombExplosions[i].active = false;
        bombExplosions[i].currentFrame = 0;
      } else if (bombExplosions[i].currentFrame >= 0) {
        animation(ExplodeFrames, bombExplosions[i].currentFrame, bombExplosions[i].position);
        bombExplosions[i].currentFrame += 1;
      }
    }
  }
  EndDrawing();
}

void UnloadGame(void) {
  for (int i = 0; i < 3; i++) { // Unload textures
    UnloadTexture(LaikaFrames[i]);
    UnloadTexture(MegaChonkerFrames[i]);
    UnloadTexture(BombFrames[i]);
    UnloadTexture(ExplodeFrames[i]);
  }
  UnloadTexture(bg);
  UnloadTexture(bg_yard);
  UnloadTexture(score_board);
  UnloadTexture(Laika1);
  UnloadTexture(MegaChonker1);
  UnloadTexture(Bomb1);
  CloseWindow();
}