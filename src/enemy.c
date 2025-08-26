#include "enemy.h"
#include <math.h>
#include <raylib.h>
#include <stdlib.h>

void InitEnemies(Enemy *enemies) {
  for (int i = 0; i < MAX_ENEMIES; i++) {
    enemies[i].active = false;
    enemies[i].speed = 200.0f;
  }
}

void SpawnEnemy(Enemy *enemies) {
  for (int i = 0; i < MAX_ENEMIES; i++) {
    if (!enemies[i].active) {
      enemies[i].active = true;
      int side = rand() % 4;
      if (side == 0)
        enemies[i].position = (Vector2){-20, rand() % 450};
      else if (side == 1)
        enemies[i].position = (Vector2){820, rand() % 450};
      else if (side == 2)
        enemies[i].position = (Vector2){rand() % 800, -20};
      else
        enemies[i].position = (Vector2){rand() % 800, 470};
      enemies[i].size = (Vector2){30, 30};
      enemies[i].color = BLUE;
      break;
    }
  }
}

void UpdateEnemies(Enemy *enemies, Vector2 playerPosition) {
  float delta = GetFrameTime();
  for (int i = 0; i < MAX_ENEMIES; i++) {
    if (enemies[i].active) {
      Vector2 direction = {playerPosition.x - enemies[i].position.x,
                           playerPosition.y - enemies[i].position.y};
      float length =
          sqrt(direction.x * direction.x + direction.y * direction.y);
      direction.x /= length;
      direction.y /= length;
      enemies[i].position.x += direction.x * delta * enemies->speed;
      enemies[i].position.y += direction.y * delta * enemies->speed;
    }
  }
}

void DrawEnemies(Enemy *enemies) {
  for (int i = 0; i < MAX_ENEMIES; i++) {
    if (enemies[i].active) {
      DrawRectangleV(enemies[i].position, enemies[i].size, enemies[i].color);
    }
  }
}
