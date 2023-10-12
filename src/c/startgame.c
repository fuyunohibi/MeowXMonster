#include "../../include/raylib.h"
#include "../../include/raymath.h"
#include "character/character.h"
#include <stdio.h>
#include <string.h>

extern void start_game(void);
extern Vector2 get_center(Texture2D texture);

enum GameScreen { MAIN_MENU, GAMEPLAY, SETTINGS };
enum ButtonState { NORMAL, MOUSE_HOVER, MOUSE_DOWN };

Texture2D startgamebg;
Texture2D button;

int CheckButtonPress(int x, int y, int width, int height) {
    int mouseX = GetMouseX();
    int mouseY = GetMouseY();

    if (CheckCollisionPointRec((Vector2){(float)mouseX, (float)mouseY}, (Rectangle){(float)x, (float)y, (float)width, (float)height})) {
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            printf("button pressed\n");
            return 1;
        } else {
            return 0;
        }
    }

    return NORMAL;
}


int intropage(void) {
    // Initialization
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "Screen Switching Example");
    SetTargetFPS(60);

    startgamebg = LoadTexture("assets/images/background/Introbg.png");
    button = LoadTexture("assets/images/background/Butt.png");


    enum GameScreen currentScreen = MAIN_MENU;

    while (!WindowShouldClose()) {
        DrawTexture(startgamebg, 0, 0, WHITE);
        // Input handling
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            int mouseX = GetMouseX();
            int mouseY = GetMouseY();

            // Check if the button is pressed based on the current screen
            if (currentScreen == MAIN_MENU) {
                if (CheckButtonPress(10, 10, button.width, button.height) == 1) {
                    currentScreen = GAMEPLAY;
                    start_game();
                } else if (CheckButtonPress(100, 200, 200, 50) == 1) {
                    currentScreen = SETTINGS;
                }
            } else if (currentScreen == SETTINGS) {
                if (CheckButtonPress(100, 350, 200, 50) == 1) {
                    currentScreen = MAIN_MENU;
                }
            } else if (currentScreen == GAMEPLAY) {
                if (CheckButtonPress(10, 10, 100, 30) == 1) {
                    currentScreen = MAIN_MENU;
                }
            }
        }

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw content based on the current screen
        if (currentScreen == MAIN_MENU) {
            DrawTexture(button, 10, 10, WHITE);
        } else if (currentScreen == SETTINGS) {
            // Draw your settings content here
        } else if (currentScreen == GAMEPLAY) {
            // Draw your gameplay content here
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}

// void DrawButton(const Texture2D *pic, Vector2 position, int width, int height, enum ButtonState state) {
    // Color textColor = DARKGRAY;
    // Color buttonColor = LIGHTGRAY;

    // Adjust colors based on the button state
    // if (state == MOUSE_HOVER) {
    //     buttonColor = GRAY;
    // } else if (state == MOUSE_DOWN) {
    //     buttonColor = DARKGRAY;
    //     textColor = RAYWHITE;
    // }

    // Draw the button rectangle and text
    // DrawRectangleV(position, (Vector2){width, height}, buttonColor);

    // DrawTexture(Button, get_center(button).x, get_center(button).y);
// }
