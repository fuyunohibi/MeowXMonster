#include "../constant/game_constants.h"

// ==================== PLAYABLE CHARACTERS ====================

Character Laika = {
    .name = "Laika",
    .price = 100,
    .HP = 200,
    .isAlive = true,
    .attackDamage = 150,
    .attackPerSecond = 0.0,
};

Character FartCat = {
    .name = "FartCat",
    .price = 250,
    .HP = 300,
    .isAlive = true,
    .attackDamage = 250,
    .attackPerSecond = 0.0,
};

Character MegaChonker = {
    .name = "MegaChonker",
    .price = 200,
    .HP = 500,
    .isAlive = true,
    .attackDamage = 0,
    .attackPerSecond = 0.0,
};

Character Bomb = {
    .name = "Bomb",
    .price = 400,
    .HP = 100,
    .isAlive = true,
    .attackDamage = 350,
    .attackPerSecond = 0.0,
};



// ==================== MONSTER CHARACTERS ====================

MonsterCharacter Jelly = {
    .name = "Jelly The Monster",
    .killReward = 100,
    .HP = 150,
    .rateOfSpawn = 0.0,
    .isAlive = true,
    .attackDamage = 100,
    .attackPerSecond = 0.0,
};

MonsterCharacter Muscle = {
    .name = "Muscle The Monster",
    .killReward = 300,
    .HP = 150,
    .rateOfSpawn = 0.0,
    .isAlive = true,
    .attackDamage = 100,
    .attackPerSecond = 0.0,
};

MonsterCharacter Ufo = {
    .name = "Ufo The Monster",
    .killReward = 500,
    .HP = 150,
    .rateOfSpawn = 0.0, 
    .isAlive = true,
    .attackDamage = 100,
    .attackPerSecond = 0.0,
};