#include "../constant/game_constants.h"

// ==================== PLAYABLE CHARACTERS ====================

Character Laika = {
    .name = 1.0,
    .price = 100.0,
    .HP = 150000.0,
    .isAlive = true,
    .attackDamage = 37500.0,
    .attackPerSecond = 0.45,
    .rightBoundery = 180.0,
};

Character MegaChonker = {
    .name = 3.0,
    .price = 200.0,
    .HP = 400000.0,
    .isAlive = true,
    .attackDamage = 0.0,
    .attackPerSecond = 0.0,
    .rightBoundery = 180.0,
};

Character Bomb = {
    .name = 4.0,
    .price = 400.0,
    .HP = 1.0,
    .isAlive = true,
    .attackDamage = 500000.0,
    .attackPerSecond = 0.0,
    .rightBoundery = 180.0,
};



// ==================== MONSTER CHARACTERS ====================
// ============ ASCENDING BASE ON STRENTH OF MONSTER ============

// AVG ATTACK OF CAT IS 750
// AVG HP OF CAT IS 500

MonsterCharacter Jelly = {
    .name = 1.0,
    .killReward = 25.0,
    .HP = 150000.0,
    .rateOfSpawn = 40.0,
    .isAlive = true,
    .attackDamage = 80.0,
    .attackPerSecond = 0.0,
    .walkSpeed = 6.0,
};

MonsterCharacter Ufo = {
    .name = 2.0,
    .killReward = 50.0,
    .HP = 250000.0,
    .rateOfSpawn = 25.0,
    .isAlive = true,
    .attackDamage = 120,
    .attackPerSecond = 0.0,
    .walkSpeed = 5.5,
};

MonsterCharacter Muscle = {
    .name = 3.0,
    .killReward = 80.0,
    .HP = 500000.0,
    .rateOfSpawn = 20.0,
    .isAlive = true,
    .attackDamage = 150.0,
    .attackPerSecond = 0.0,
    .walkSpeed = 5.0,
};