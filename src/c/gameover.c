#include <stdio.h>
#include <string.h>
#include <raylib.h>
#include <GLFW/glfw3.h>

extern void intropage(void);
extern int get_total_score(void);

Texture2D gameoverBg;
Texture2D yesButton;
Texture2D noButton;

int CheckOptionPress(int x, int y, int width, int height)
{
    int mouseX = GetMouseX();
    int mouseY = GetMouseY();
    // printf("mouseX: %d, mouseY: %d\n", mouseX, mouseY);

    if (CheckCollisionPointRec((Vector2){(float)mouseX, (float)mouseY}, (Rectangle){x, y, width, height})) {
        return 1;
    } else {
        return 0;
    }
}

int GameOverPage(void)
{
    // Initialization
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "MeowXMonster");

    SetTargetFPS(60);

    gameoverBg = LoadTexture("../assets/images/background/Gameover.png");
    yesButton = LoadTexture("../assets/images/background/Yes.png");
    noButton = LoadTexture("../assets/images/background/No.png");

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        char scoreText[100];
        int score = get_total_score();
        snprintf(scoreText, sizeof(scoreText), "Score: %d", score);

        DrawTexture(gameoverBg, 0, 0, WHITE);
        DrawText(scoreText, 100, 100, 30, BLACK);
        DrawTexture(yesButton, 650, 780, WHITE);
        DrawTexture(noButton, 1000, 780, WHITE);

        EndDrawing();

        // Input handling
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            if (CheckOptionPress(650, 780, yesButton.width, yesButton.height) == 1) {
                CloseWindow();
                intropage();
            } else if (CheckOptionPress(1000, 780, noButton.width, noButton.height) == 1) {
                CloseWindow();
            }
        }
    }

    CloseWindow();

    return 0;
}