
#include "raylib.h"
#include "game.h"
#include <time.h>
#include <stdlib.h>

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "RoguedDeluxe");

    Player player;
    Bullet bullets[MAX_BULLETS];
    Enemy enemies[MAX_ENEMIES];
    PowerUp powerUps[MAX_POWERUPS];
    int score;
    bool gameOver;

    srand(time(NULL));

    InitGame(&player, bullets, enemies, powerUps, &score, &gameOver);

    float fireTimer = 0.0f;
    float enemySpawnTimer = 0.0f;
    float powerUpSpawnTimer = 0.0f;

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        if (!gameOver)
        {
            UpdateGame(&player, bullets, enemies, powerUps, &score, &gameOver, &fireTimer, &enemySpawnTimer, &powerUpSpawnTimer);
        }
        else
        {
            if (IsKeyPressed(KEY_R))
            {
                InitGame(&player, bullets, enemies, powerUps, &score, &gameOver);
            }
        }

        DrawGame(player, bullets, enemies, powerUps, score, gameOver);
    }

    CloseWindow();

    return 0;
}
