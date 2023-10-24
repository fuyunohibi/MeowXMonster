#ifndef GAME_CONSTANTS_H
#define GAME_CONSTANTS_H

#include <raylib.h>

#define NUM_FRAMES 3
#define NUM_BLOCKS 15
#define NUM_POSITIONS 3

typedef struct
{
  float name;
  float price;
  float HP;
  bool isAlive;
  float attackDamage;
  float attackPerSecond;
  float attackTimer;
  Texture2D frames[NUM_FRAMES];
  bool shouldDrawAnimation[NUM_BLOCKS];
  int blockPosition;
  float rightBoundery;
} Character;

typedef struct
{
  float name;
  float killReward;
  float rateOfSpawn;
  float HP;
  bool isAlive;
  float attackDamage;
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