#ifndef GAME_FUNCTIONS_H
#define GAME_FUNCTIONS_H

#include "game_data.h"

// Function prototypes
Vector2 get_center(Texture2D texture);
void animation(Texture2D frames[NUM_FRAMES], int currentFrame, float frameTimer, const char *name, Vector2 position);
void load_animation(Texture2D frames[NUM_FRAMES], const char *name);
bool IsMouseOverBox(Vector2 mousePosition, Vector2 boxPosition, Texture2D Box);
void CopyImage(Vector2 *imagePosition, Vector2 targetPosition, Texture2D image);
void InitializeGame(void);
void UpdateGame(void);
void DrawGame(void);
void UnloadGame(void);
void GameOver(void);

#endif // GAME_FUNCTIONS_H

