
#include "game.h"
#include <stdio.h>

void InitGame(Player *player, Bullet *bullets, Enemy *enemies, PowerUp *powerUps, int *score, bool *gameOver)
{
    InitPlayer(player);
    InitBullets(bullets);
    InitEnemies(enemies);
    InitPowerUps(powerUps);
    *score = 0;
    *gameOver = false;
}

void UpdateGame(Player *player, Bullet *bullets, Enemy *enemies, PowerUp *powerUps, int *score, bool *gameOver, float *fireTimer, float *enemySpawnTimer, float *powerUpSpawnTimer)
{
    *fireTimer += GetFrameTime();
    *enemySpawnTimer += GetFrameTime();
    *powerUpSpawnTimer += GetFrameTime();

    UpdatePlayer(player, *fireTimer);
    FireBullet(bullets, player->position, *fireTimer, player->fireRate);
    if (*fireTimer >= player->fireRate && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) *fireTimer = 0;

    if (*enemySpawnTimer >= 1.0f)
    {
        SpawnEnemy(enemies);
        *enemySpawnTimer = 0.0f;
    }

    if (*powerUpSpawnTimer >= 10.0f)
    {
        SpawnPowerUp(powerUps);
        *powerUpSpawnTimer = 0.0f;
    }

    UpdateEnemies(enemies, player->position);
    UpdatePowerUps(powerUps, player);
    UpdateBullets(bullets);

    for (int i = 0; i < MAX_BULLETS; i++)
    {
        if (bullets[i].active)
        {
            for (int j = 0; j < MAX_ENEMIES; j++)
            {
                if (enemies[j].active && CheckCollisionRecs((Rectangle){bullets[i].position.x, bullets[i].position.y, bullets[i].size.x, bullets[i].size.y}, (Rectangle){enemies[j].position.x, enemies[j].position.y, enemies[j].size.x, enemies[j].size.y}))
                {
                    bullets[i].active = false;
                    enemies[j].active = false;
                    *score += 10;
                }
            }
        }
    }

    for (int i = 0; i < MAX_ENEMIES; i++)
    {
        if (enemies[i].active && CheckCollisionRecs((Rectangle){player->position.x, player->position.y, player->size.x, player->size.y}, (Rectangle){enemies[i].position.x, enemies[i].position.y, enemies[i].size.x, enemies[i].size.y}))
        {
            *gameOver = true;
        }
    }
}

void DrawGame(Player player, Bullet *bullets, Enemy *enemies, PowerUp *powerUps, int score, bool gameOver)
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    if (!gameOver)
    {
        DrawPlayer(player);
        DrawEnemies(enemies);
        DrawBullets(bullets);
        DrawPowerUps(powerUps);

        char scoreText[20];
        sprintf(scoreText, "Score: %d", score);
        DrawText(scoreText, 10, 10, 20, LIGHTGRAY);
    }
    else
    {
        DrawText("GAME OVER", 800 / 2 - MeasureText("GAME OVER", 40) / 2, 450 / 2 - 20, 40, RED);
        DrawText("Press 'R' to restart", 800 / 2 - MeasureText("Press 'R' to restart", 20) / 2, 450 / 2 + 20, 20, GRAY);
    }

    EndDrawing();
}
