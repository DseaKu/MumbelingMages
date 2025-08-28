#include "enemy.h"
#include "animation_handler.h"
#include "enemy_properties.h"
#include "raymath.h"
#include "sprite.h"
#include <float.h>
#include <math.h>
#include <raylib.h>
#include <stdlib.h>

void InitEnemies(Enemy *enemies) {
  for (int i = 0; i < MAX_ENEMIES; i++) {
    enemies[i].sprite = GOBLIN;
  }
}

void SpawnEnemy(Enemy *enemies, Map map, Vector2 player_position) {
  // Block enemy[0] to spawn, this index is reserved for other logic e.g.

  for (int i = 1; i < MAX_ENEMIES; i++) {
    if (!enemies[i].active && !(enemies[i].state & SPAWNING)) {
      enemies[i].state |= SPAWNING;
      enemies[i] = GetEnemyProperties(enemies[i].sprite);
      enemies[i].state = SPAWNING;
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

void UpdateEnemies(Enemy *enemies, Vector2 playerPosition) {
  float delta = GetFrameTime();
  float safe_zone_distance = 80.0f;
  for (int i = 0; i < MAX_ENEMIES; i++) {

    // Spawning
    if (enemies[i].state & SPAWNING) {
      enemies[i].spawn_timer -= delta;

      // Spawning finshed
      if (enemies[i].spawn_timer <= 0) {
        enemies[i].active = true;
        enemies[i].state -= SPAWNING;
      }
      // Walking
    } else if (enemies[i].active) {
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
      enemies[i].state |= WALK;
    }
  }

  // Enemy collision logic to prevent stacking
  float separation_force = 1.5f;
  for (int i = 0; i < MAX_ENEMIES; i++) {
    if (!enemies[i].active)
      continue;
    for (int j = i + 1; j < MAX_ENEMIES; j++) {
      if (!enemies[j].active)
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

void DrawEnemies(Enemy *enemies) {
  for (int i = 0; i < MAX_ENEMIES; i++) {
    if (enemies[i].active) {

      if (enemies[i].state & SPAWNING) {
        DrawSprite(enemies[i].hit_box, enemies[i].position,
                   &enemies[i].animation, enemies[i].sprite, SPAWNING);
        continue;
      }

      if (enemies[i].state & WALK) {
        DrawSprite(enemies[i].hit_box, enemies[i].position,
                   &enemies[i].animation, enemies[i].sprite, WALK);
        continue;
      }
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
