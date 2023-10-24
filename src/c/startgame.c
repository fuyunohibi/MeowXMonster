#include <stdio.h>
#include <string.h>
#include <raylib.h>
#include <GLFW/glfw3.h>

extern void start_game(void);

Texture2D startgamebg;
Texture2D button;

int CheckButtonPress(int x, int y, int width, int height) {
    int mouseX = GetMouseX();
    int mouseY = GetMouseY();
    //printf("mouseX: %d, mouseY: %d\n", mouseX, mouseY);

    if (CheckCollisionPointRec((Vector2){(float)mouseX, (float)mouseY}, (Rectangle){x, y, width, height})) {
        //printf("mouseX: %d, mouseY: %d\n", mouseX, mouseY);
        return 1;
    } else {
        return 0;
    }
}


int intropage(void) {
    // Initialization
    const int screenWidth = 1920;
    const int screenHeight = 1080;
    
    InitWindow(screenWidth, screenHeight, "MeowXMonster");
    
    SetTargetFPS(60);

    startgamebg = LoadTexture("../assets/images/background/Introbg.png");
    button = LoadTexture("../assets/images/background/Butt.png");

<<<<<<< Updated upstream
    while (!WindowShouldClose()) {
=======

    enum GameScreen currentScreen = MAIN_MENU;
    int gameRunning = 1;

    while (!WindowShouldClose() && gameRunning) {
        DrawTexture(startgamebg, 0, 0, WHITE);
        // Input handling
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            int mouseX = GetMouseX();
            int mouseY = GetMouseY();

            // Check if the button is pressed based on the current screen
            if (currentScreen == MAIN_MENU) {
                if (CheckButtonPress(10, 10, button.width, button.height) == 1) {
                    currentScreen = GAMEPLAY;
                    // CloseWindow();
                    start_game();
                    // gameRunning = 0;
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
                    gameRunning = 1;
                }
            }
        }

        // Draw
>>>>>>> Stashed changes
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawTexture(startgamebg, 0, 0, WHITE);
        DrawTexture(button, 0, 0, WHITE);

        EndDrawing();

        // Input handling
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (CheckButtonPress(720, 690, 480, 130) == 1)
            {
                start_game();
            }
        }
    }

    CloseWindow();

    return 0;
}