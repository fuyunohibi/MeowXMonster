#include <stdio.h>
#include "./src/c/character_asm/game_asm.h"

extern void intropage(void);

<<<<<<< HEAD
void printCharacter(const Character* c) {
    printf("Name: %s\n", c->name);
    printf("Price: %d\n", c->price);
    printf("HP: %d\n", c->HP);
    printf("Is Alive: %d\n", (int)c->isAlive);
    printf("Attack Damage: %.2f\n", c->attackDamage);
    printf("Attack Per Second: %.2f\n", c->attackPerSecond);
    printf("Right Boundary: %.2f\n", c->rightBoundery);
    // ... print any additional fields
    printf("\n");
}

int main () {
=======
int main(void) {
>>>>>>> origin/master
  printf("Starting MoewXMonster...\n");

  Character Laika;
  createLaika(&Laika);
  printCharacter(&Laika);

  Character FartCat;
  createFartCat(&FartCat);
  printCharacter(&FartCat);

  printf("Name: %s\n", Laika.name);
  intropage();
  return 0;
}
