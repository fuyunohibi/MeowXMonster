#ifndef GAME_CONSTANTS_H
#define GAME_CONSTANTS_H

#include "../../../include/raylib.h"

#define NUM_FRAMES 3
#define NUM_BLOCKS 15
#define NUM_POSITIONS 3

typedef struct
{
  char name[50];
  int price;
  int HP;
  bool isAlive;
  int attackDamage;
  float attackPerSecond;
  float attackTimer;
  Texture2D frames[NUM_FRAMES];
  bool shouldDrawAnimation[NUM_BLOCKS];
  int blockPosition;
} Character;

typedef struct
{
  char name[50];
  int killReward;
  float rateOfSpawn;
  int HP;
  bool isAlive;
  int attackDamage;
  float attackPerSecond;
  float attackTimer;
  Texture2D frames[NUM_FRAMES];
  bool shouldDrawAnimation[NUM_BLOCKS];
  Vector2 position;
  bool active;
  float animationTimer;
  float walkSpeed;
  int row;
} MonsterCharacter;

#endif