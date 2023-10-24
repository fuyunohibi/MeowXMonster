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

    while (!WindowShouldClose()) {
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