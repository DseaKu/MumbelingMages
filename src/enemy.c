#include "enemy.h"
#include "raymath.h"
#include <float.h>
#include <raylib.h>
#include <stdlib.h>

void InitEnemies(Enemy *enemies) {
  for (int i = 0; i < MAX_ENEMIES; i++) {
    enemies[i].speed = 150.0f;
  }
}

void SpawnEnemy(Enemy *enemies, Map map, Vector2 player_position) {
  // Block enemy[0] to spawn, this index is reserved for other logic e.g.
  float spawn_distance = 10.0f;
  float time2spawn = 2.0f;
  int health = 100;
  for (int i = 1; i < MAX_ENEMIES; i++) {
    if (!enemies[i].active && !enemies[i].spawning) {
      enemies[i].spawning = true;
      enemies[i].health = health;
      enemies[i].spawnTimer = time2spawn;
      Vector2 spawn_position;
      do {
        spawn_position = (Vector2){rand() % map.width, rand() % map.height};
      } while (Vector2DistanceSqr(player_position, spawn_position) <
               spawn_distance * spawn_distance);

      enemies[i].position = spawn_position;
      enemies[i].size = (Vector2){30, 30};
      enemies[i].color = RED;

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
                 enemies[i].size.x / 2 * (1 - enemies[i].spawnTimer), RED);
    } else if (enemies[i].active) {
      DrawRectangleV(enemies[i].position, enemies[i].size, enemies[i].color);
    }
  }
}
int GetClosestEnemy(Enemy *enemies, Vector2 position) {
  float closest_distance_sq = FLT_MAX;
  int closest_enemy_index = -1;

  for (int i = 0; i < MAX_ENEMIES; i++) {
    Enemy enemy = enemies[i];
    if (enemy.active) {
      float current_distance_sq = Vector2DistanceSqr(enemy.position, position);
      if (current_distance_sq < closest_distance_sq) {
        closest_distance_sq = current_distance_sq;
        closest_enemy_index = i;
      }
    }
  }

  return closest_enemy_index;
}
