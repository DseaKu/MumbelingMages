#include "enemy.h"
#include "animation_handler.h"
#include "enemy_properties.h"
#include "raymath.h"
#include <float.h>
#include <math.h>
#include <raylib.h>
#include <stdlib.h>

void InitEnemies(Enemy *enemies) {
  for (int i = 0; i < MAX_ENEMIES; i++) {
    enemies[i].id = GOBLIN;
    enemies[i].is_facing_right = true;
  }
}

void SpawnEnemy(Enemy *enemies, Map map, Vector2 player_position) {
  // Block enemy[0] to spawn, this index is reserved for other logic e.g.

  for (int i = 1; i < MAX_ENEMIES; i++) {
    if (!enemies[i].active && !enemies[i].spawning) {
      enemies[i] = GetEnemyProperties(enemies[i].id);
      enemies[i].spawning = true;
      enemies[i].currentFrame = 0;
      enemies[i].frameTimer = 0.0f;
      enemies[i].hit_cooldown = 0.0f;
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
    if (enemies[i].spawning) {
      enemies[i].spawnTimer -= delta;
      if (enemies[i].spawnTimer <= 0) {
        enemies[i].spawning = false;
        enemies[i].active = true;
      }
    } else if (enemies[i].active) {
      Vector2 direction = Vector2Subtract(playerPosition, enemies[i].position);
      enemies[i].is_facing_right = (direction.x > 0);

      if (Vector2Length(direction) > safe_zone_distance) {
        direction = Vector2Normalize(direction);
        enemies[i].position.x += direction.x * delta * enemies[i].speed;
        enemies[i].position.y += direction.y * delta * enemies[i].speed;
      }

      if (enemies[i].hit_cooldown > 0) {
        enemies[i].hit_cooldown -= delta;
      }

      enemies[i].frameTimer += delta;
      if (enemies[i].frameTimer >= enemies[i].frameDuration) {
        enemies[i].frameTimer = 0.0f;
        enemies[i].currentFrame++;
        if (enemies[i].currentFrame >= enemies[i].frameCount) {
          enemies[i].currentFrame = 0;
        }
      }
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
                          enemies[i].size.x, enemies[i].size.y};
      Rectangle rect_j = {enemies[j].position.x, enemies[j].position.y,
                          enemies[j].size.x, enemies[j].size.y};

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
    if (enemies[i].spawning) {
      DrawCircle(enemies[i].position.x, enemies[i].position.y,
                 enemies[i].size.x / 2 * (1 - enemies[i].spawnTimer), RED);
    } else if (enemies[i].active) {

      Texture2D texture =
          GetEnemyTexture(enemies[i].id, enemies[i].anmimation_id);

      // Change drawing size of enemy animation
      float frameWidth = (float)texture.width / enemies[i].frameCount;
      Rectangle sourceRec = {(float)enemies[i].currentFrame * frameWidth, 0,
                             frameWidth, (float)texture.height};

      if (!enemies[i].is_facing_right) {
        sourceRec.width *= -1;
      }

      float visual_width = enemies[i].size.x * enemies[i].texture_scale;
      float visual_height = enemies[i].size.y * enemies[i].texture_scale;

      Rectangle destRec = {enemies[i].position.x, enemies[i].position.y,
                           visual_width, visual_height};
      Vector2 origin = {visual_width / 2, visual_height / 2};

      DrawTexturePro(texture, sourceRec, destRec, origin, 0, WHITE);
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
