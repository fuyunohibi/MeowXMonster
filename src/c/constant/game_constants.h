#ifndef GAME_CONSTANTS_H
#define GAME_CONSTANTS_H

#include "../../../include/raylib.h"

#define NUM_FRAMES 3
#define NUM_BLOCKS 15

typedef struct
{
  char name[50];
  int HP;
  int attackDamage;
  float attackPerSecond;
  Texture2D frames[NUM_FRAMES];
  bool shouldDrawAnimation[NUM_BLOCKS];
} Character;

#endif
