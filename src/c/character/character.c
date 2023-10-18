#include "../constant/game_constants.h"

// ==================== PLAYABLE CHARACTERS ====================

Character Laika = {
    .name = "Laika",
    .price = 100,
    .HP = 20000,
    .isAlive = true,
    .attackDamage = 50,
    .attackPerSecond = 0.5,
    .rightBoundery = 180.0,
};

Character FartCat = {
    .name = "FartCat",
    .price = 250,
    .HP = 50000,
    .isAlive = true,
    .attackDamage = 1,
    .attackPerSecond = 0.05,
    .rightBoundery = 0.0,
};

Character MegaChonker = {
    .name = "MegaChonker",
    .price = 200,
    .HP = 400000,
    .isAlive = true,
    .attackDamage = 0,
    .attackPerSecond = 0.0,
    .rightBoundery = 180.0,
};

Character Bomb = {
    .name = "Bomb",
    .price = 400,
    .HP = 50,
    .isAlive = true,
    .attackDamage = 350,
    .attackPerSecond = 0.0,
    .rightBoundery = 180.0,
};

// ==================== MONSTER CHARACTERS ====================
// ============ ASCENDING BASE ON STRENTH OF MONSTER ============

// AVG ATTACK OF CAT IS 750
// AVG HP OF CAT IS 500

MonsterCharacter Jelly = {
    .name = "Jelly The Monster",
    .killReward = 100,
    .HP = 150,
    .rateOfSpawn = 40.0,
    .isAlive = true,
    .attackDamage = 80,
    .attackPerSecond = 0.0,
    .walkSpeed = 5.0,
};

MonsterCharacter Ufo = {
    .name = "Ufo The Monster",
    .killReward = 500,
    .HP = 250,
    .rateOfSpawn = 25.0,
    .isAlive = true,
    .attackDamage = 120,
    .attackPerSecond = 0.0,
    .walkSpeed = 4.5,
};

MonsterCharacter Muscle = {
    .name = "Muscle The Monster",
    .killReward = 300,
    .HP = 400,
    .rateOfSpawn = 20.0,
    .isAlive = true,
    .attackDamage = 100,
    .attackPerSecond = 0.0,
    .walkSpeed = 4.0,
};

MonsterCharacter Longleg = {
    .name = "Longleg The Monster",
    .killReward = 500,
    .HP = 600,
    .rateOfSpawn = 15.0,
    .isAlive = true,
    .attackDamage = 200,
    .attackPerSecond = 0.0,
    .walkSpeed = 3.5,
};