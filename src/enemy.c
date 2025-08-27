#include "enemy.h"
#include "raymath.h"
#include "window.h"
#include <raylib.h>
#include <stdlib.h>

void InitEnemies(Enemy *enemies) {
  for (int i = 0; i < MAX_ENEMIES; i++) {
    enemies[i].speed = 150.0f;
  }
}

void SpawnEnemy(Enemy *enemies) {
  // Block enemy[0] to spawn, this index is reserved for other logic e.g.
  // auto-aim
  for (int i = 1; i < MAX_ENEMIES; i++) {
    if (!enemies[i].active && !enemies[i].spawning) {
      enemies[i].spawning = true;
      enemies[i].spawnTimer = 2.0f;
      enemies[i].position =
          (Vector2){rand() % GetDisplayWidth(), rand() % GetDisplayHeigth()};
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
int GetClosestEnemy(Enemy *enemies, Vector2 position) {

  float closest_enemy_position = 0;
  int closest_enemy_index;
  for (int i = 0; i < MAX_ENEMIES; i++) {
    Enemy enemy = enemies[i];
    if (enemy.active) {
      float dx = enemy.position.x - position.x;
      float dy = enemy.position.y - position.y;
      float current_distance = (dx * dx) + (dy * dy);
      if (current_distance > closest_enemy_position) {
        closest_enemy_index = i;
      }
    }
  }

  return closest_enemy_index;
}
