#include "enemy.h"
#include <stdlib.h>
#include <math.h>

void InitEnemies(Enemy *enemies)
{
    for (int i = 0; i < MAX_ENEMIES; i++)
    {
        enemies[i].active = false;
    }
}

void SpawnEnemy(Enemy *enemies)
{
    for (int i = 0; i < MAX_ENEMIES; i++)
    {
        if (!enemies[i].active)
        {
            enemies[i].active = true;
            int side = rand() % 4;
            if (side == 0) enemies[i].position = (Vector2){ -20, rand() % 450 };
            else if (side == 1) enemies[i].position = (Vector2){ 820, rand() % 450 };
            else if (side == 2) enemies[i].position = (Vector2){ rand() % 800, -20 };
            else enemies[i].position = (Vector2){ rand() % 800, 470 };
            enemies[i].size = (Vector2){ 30, 30 };
            enemies[i].color = BLUE;
            break;
        }
    }
}

void UpdateEnemies(Enemy *enemies, Vector2 playerPosition)
{
    for (int i = 0; i < MAX_ENEMIES; i++)
    {
        if (enemies[i].active)
        {
            Vector2 direction = { playerPosition.x - enemies[i].position.x, playerPosition.y - enemies[i].position.y };
            float length = sqrt(direction.x * direction.x + direction.y * direction.y);
            direction.x /= length;
            direction.y /= length;
            enemies[i].position.x += direction.x * 2.0f;
            enemies[i].position.y += direction.y * 2.0f;
        }
    }
}

void DrawEnemies(Enemy *enemies)
{
    for (int i = 0; i < MAX_ENEMIES; i++)
    {
        if (enemies[i].active)
        {
            DrawRectangleV(enemies[i].position, enemies[i].size, enemies[i].color);
        }
    }
}