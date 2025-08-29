#include "enemy.h"
#include "animation_handler.h"
#include "enemy_properties.h"
#include "raymath.h"
#include "sprite.h"
#include <float.h>
#include <math.h>
#include <raylib.h>
#include <stdbool.h>
#include <stdlib.h>

void InitEnemies(EnemyData *enemy_data) {

  for (int i = 0; i < MAX_ENEMIES; i++) {
    enemy_data->state[i] = INACTIVE;
    enemy_data->enemies[i].sprite = GOBLIN;
  }
}

void SpawnEnemy(EnemyData *enemy_data, Map map, Vector2 player_position) {

  Enemy *enemies = enemy_data->enemies;
  // Block enemy[0] to spawn, this index is reserved for other logic e.g.
  for (int i = 1; i < MAX_ENEMIES; i++) {

    if (enemy_data->state[i] == INACTIVE) {
      enemies[i] = GetEnemyProperties(enemies[i].sprite);
      enemy_data->state[i] = SPAWNING;
      Vector2 spawn_position;
      do {
        spawn_position = (Vector2){rand() % map.width, rand() % map.height};
      } while (Vector2DistanceSqr(player_position, spawn_position) <
               pow(enemies->spawn_distance, 2.0f));

      enemies[i].position = spawn_position;
      enemies[i].color = RED;

      break;
    }
  }
}

void UpdateEnemies(EnemyData *enemy_data, Vector2 playerPosition) {
  float delta = GetFrameTime();
  Enemy *enemies = enemy_data->enemies;
  float safe_zone_distance = 80.0f;
  for (int i = 0; i < MAX_ENEMIES; i++) {

    // Spawning
    if (enemy_data->state[i] == SPAWNING) {
      enemies[i].spawn_timer -= delta;
      // Spawning finshed
      if (enemies[i].spawn_timer <= 0) {
        enemy_data->state[i] = WALK;
      }
    }

    // Walking
    if (enemy_data->state[i] == WALK) {
      Vector2 direction = Vector2Subtract(playerPosition, enemies[i].position);
      enemies[i].animation.is_facing_right = (direction.x > 0);

      if (Vector2Length(direction) > safe_zone_distance) {
        direction = Vector2Normalize(direction);
        enemies[i].position.x += direction.x * delta * enemies[i].speed;
        enemies[i].position.y += direction.y * delta * enemies[i].speed;
      }

      if (enemies[i].hit_cooldown > 0) {
        enemies[i].hit_cooldown -= delta;
      }
    }
  }

  // Enemy collision logic to prevent stacking
  float separation_force = 1.5f;
  for (int i = 0; i < MAX_ENEMIES; i++) {
    if (enemy_data->state[i] == INACTIVE)
      continue;
    for (int j = i + 1; j < MAX_ENEMIES; j++) {
      if (enemy_data->state[j] == INACTIVE)
        continue;

      Rectangle rect_i = {enemies[i].position.x, enemies[i].position.y,
                          enemies[i].hit_box.x, enemies[i].hit_box.y};
      Rectangle rect_j = {enemies[j].position.x, enemies[j].position.y,
                          enemies[j].hit_box.x, enemies[j].hit_box.y};

      if (CheckCollisionRecs(rect_i, rect_j)) {
        Vector2 push_direction =
            Vector2Subtract(enemies[i].position, enemies[j].position);
        if (push_direction.x == 0 && push_direction.y == 0) {
          push_direction.x = (float)(rand() % 100 - 50);
          push_direction.y = (float)(rand() % 100 - 50);
        }
        Vector2 normalized_push = Vector2Normalize(push_direction);

        enemies[i].position.x += normalized_push.x * separation_force * delta;
        enemies[i].position.y += normalized_push.y * separation_force * delta;
        enemies[j].position.x -= normalized_push.x * separation_force * delta;
        enemies[j].position.y -= normalized_push.y * separation_force * delta;
      }
    }
  }
}

void DrawEnemies(EnemyData *enemy_data) {
  Enemy *enemies = enemy_data->enemies;
  for (int i = 0; i < MAX_ENEMIES; i++) {
    if (enemy_data->state[i] != INACTIVE) {
      PlayAnimation(enemies[i].hit_box, enemies[i].position,
                    &enemies[i].animation, enemies[i].sprite,
                    enemy_data->state[i]);
    }
  }
}
int GetClosestEnemy(EnemyData *enemy_data, Vector2 position) {
  Enemy *enemies = enemy_data->enemies;
  float closest_distance_sq = FLT_MAX;
  int closest_enemy_index = -1;

  for (int i = 0; i < MAX_ENEMIES; i++) {
    if (enemy_data->state[i] != INACTIVE) {
      float current_distance_sq =
          Vector2DistanceSqr(enemies[i].position, position);
      if (current_distance_sq < closest_distance_sq) {
        closest_distance_sq = current_distance_sq;
        closest_enemy_index = i;
      }
    }
  }

  return closest_enemy_index;
}
