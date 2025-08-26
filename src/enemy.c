#include "enemy.h"
#include "raymath.h"
#include <raylib.h>
#include <stdlib.h>

void InitEnemies(Enemy *enemies) {
  for (int i = 0; i < MAX_ENEMIES; i++) {
    enemies[i].active = false;
    enemies[i].spawning = false;
    enemies[i].spawnTimer = 0;
    enemies[i].speed = 150.0f;
  }
}

void SpawnEnemy(Enemy *enemies, int screen_width, int screen_height) {
  for (int i = 0; i < MAX_ENEMIES; i++) {
    if (!enemies[i].active && !enemies[i].spawning) {
      enemies[i].spawning = true;
      enemies[i].spawnTimer = 1.0f;
      enemies[i].position =
          (Vector2){rand() % screen_width, rand() % screen_height};
      enemies[i].size = (Vector2){30, 30};
      enemies[i].color = BLUE;
      break;
    }
  }
}

void UpdateEnemies(Enemy *enemies, Vector2 playerPosition) {
  float delta = GetFrameTime();
  for (int i = 0; i < MAX_ENEMIES; i++) {
    if (enemies[i].spawning) {
      enemies[i].spawnTimer -= delta;
      if (enemies[i].spawnTimer <= 0) {
        enemies[i].spawning = false;
        enemies[i].active = true;
      }
    } else if (enemies[i].active) {
      Vector2 direction = Vector2Subtract(playerPosition, enemies[i].position);
      direction = Vector2Normalize(direction);
      enemies[i].position.x += direction.x * delta * enemies->speed;
      enemies[i].position.y += direction.y * delta * enemies->speed;
    }
  }
}

void DrawEnemies(Enemy *enemies) {
  for (int i = 0; i < MAX_ENEMIES; i++) {
    if (enemies[i].spawning) {
      DrawCircle(enemies[i].position.x, enemies[i].position.y,
                 enemies[i].size.x / 2 * (1 - enemies[i].spawnTimer), BLUE);
    } else if (enemies[i].active) {
      DrawRectangleV(enemies[i].position, enemies[i].size, enemies[i].color);
    }
  }
}
