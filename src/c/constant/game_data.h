#ifndef GAME_DATA_H
#define GAME_DATA_H

#include <raylib.h>
#include "../character/character.h"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define NUM_FRAMES 3
#define NUM_BLOCKS 15
#define MAX_CHARACTERS 30
#define INITIAL_REWARD 100
#define MAX_MONSTERS 50

// Global variables
Texture2D box_size = {250, 250};
Texture2D LaikaFrames[3];
Texture2D MegaChonkerFrames[3];
Texture2D BombFrames[3];
Texture2D JellyFrames[3];
Texture2D UfoFrames[3];
Texture2D MuscleFrames[3];
Texture2D bg;
Texture2D bg_yard;
Texture2D score_board;
Texture2D Laika1;
Texture2D MegaChonker1;
Texture2D Bomb1;
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
bool shouldCopyLaika = false;
bool shouldCopyMC = false;
bool shouldCopyBomb = false;
bool block_empty[NUM_BLOCKS];
bool block_contains_Laika_animation[NUM_BLOCKS];
bool block_contains_MC_animation[NUM_BLOCKS];
bool block_contains_Bomb_animation[NUM_BLOCKS];
bool shouldDrawAnimationLaika[NUM_BLOCKS] = {false};
bool shouldDrawAnimationLaika1 = false;
bool shouldDrawAnimationLaika2 = false;
bool shouldDrawAnimationMC[NUM_BLOCKS] = {false};
bool shouldDrawAnimationMC1 = false;
bool shouldDrawAnimationMC2 = false;
bool shouldDrawAnimationBomb[NUM_BLOCKS] = {false};
bool shouldDrawAnimationBomb1 = false;
bool shouldDrawAnimationBomb2 = false;
Vector2 charactersPOS[MAX_CHARACTERS];

int score = 0;
char scoreBuffer[50];
int money = 100;
char moneyBuffer[50];

Texture2D LaikaAtkTexture;
Texture2D ExplodeFrames[3];

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
  int currentFrame;
} Explosion;

MonsterCharacter jellys[MAX_MONSTERS];
MonsterCharacter ufos[MAX_MONSTERS];
MonsterCharacter muscles[MAX_MONSTERS];

float monsterSpawnTimer = 0.0f;
float monsterSpawnInterval = 80.0f; // Delay between monster spawns in seconds

#define MAX_PROJECTILES 100

Projectile laikaProjectiles[MAX_PROJECTILES];
Explosion bombExplosions[MAX_CHARACTERS];

Character charactersOnField[MAX_CHARACTERS];
int charactersCount = 0;
int charactersRow[NUM_BLOCKS];
int monsterCount = 0;


#endif // GAME_DATA_H
