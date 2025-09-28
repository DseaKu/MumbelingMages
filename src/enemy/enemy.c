#include "enemy/enemy.h"
#include "core/animation_handler.h"
#include "core/orb.h"
#include "enemy/enemy_properties.h"
#include "enemy/enemy_sprite.h"
#include "player/player.h"
#include "raymath.h"
#include <float.h>
#include <math.h>
#include <raylib.h>
#include <stdbool.h>
#include <stdlib.h>

void InitEnemies(EnemyData *enemy_data) {

  for (int i = 0; i < MAX_ENEMIES; i++) {
    enemy_data->state[i] = ENEMY_INACTIVE;
    enemy_data->enemies[i].sprite = GOBLIN;
  }
}

void SpawnEnemy(EnemyData *enemy_data, Map map, Vector2 player_position) {

  Enemy *enemies = enemy_data->enemies;
  // Block enemy[0] to spawn, this index is reserved for other logic e.g.
  for (int i = 1; i < MAX_ENEMIES; i++) {

    if (enemy_data->state[i] == ENEMY_INACTIVE) {
      enemies[i] = GetEnemyProperties(enemies[i].sprite);
      enemy_data->state[i] = ENEMY_SPAWNING;
      enemies[i].position =
          GenerateSpawnPosition(map, player_position, enemies->spawn_distance);

      break;
    }
  }
}

Vector2 GenerateSpawnPosition(Map map, Vector2 player_position,
                              float spawn_distance) {
  Vector2 spawn_position;
  do {
    spawn_position = (Vector2){rand() % map.width, rand() % map.height};
  } while (Vector2DistanceSqr(player_position, spawn_position) <
           pow(spawn_distance, 2.0f));
  return spawn_position;
}
void UpdateEnemies(EnemyData *enemy_data, Vector2 playerPosition, Map map) {

  float delta = GetFrameTime();
  float safe_zone_distance = 80.0f;
  Enemy *enemies = enemy_data->enemies;
  Vector2 direction;
  for (int i = 0; i < MAX_ENEMIES; i++) {

    Enemy *enemy = &enemy_data->enemies[i];
    EnemyState *state = &enemy_data->state[i];

    /* Enemy state mashine */
    switch (*state) {
    case ENEMY_IDLE:
      *state = ENEMY_WALKING;
      break;

    case ENEMY_SPAWNING:
      enemy->timer += delta;
      if (enemy->timer >= enemy->spawn_duration) {
        *state = ENEMY_IDLE;
        enemy->timer = 0;
      }
      break;

    case ENEMY_WALKING:
      direction = Vector2Subtract(playerPosition, enemy->position);
      enemy->animation.is_facing_right = (direction.x > 0);

      /* Avoid stacking enemies on each other */
      Rectangle rect_i = {enemy->position.x, enemy->position.y,
                          enemy->hit_box.x, enemy->hit_box.y};
      for (int j = i + 1; j < MAX_ENEMIES; j++) {
        if (enemy_data->state[j] == ENEMY_INACTIVE)
          continue;

        Rectangle rect_j = {enemies[j].position.x, enemies[j].position.y,
                            enemies[j].hit_box.x, enemies[j].hit_box.y};

        if (CheckCollisionRecs(rect_i, rect_j)) {
          Vector2 push_direction =
              Vector2Subtract(enemy->position, enemies[j].position);
          if (push_direction.x == 0 && push_direction.y == 0) {
            push_direction.x = (float)(rand() % 100 - 50);
            push_direction.y = (float)(rand() % 100 - 50);
          }
          Vector2 normalized_push = Vector2Normalize(push_direction);

          enemy->position.x +=
              normalized_push.x * ENEMY_ENEMY_COLLISION_DISTANCE * delta;
          enemy->position.y +=
              normalized_push.y * ENEMY_ENEMY_COLLISION_DISTANCE * delta;
          enemies[j].position.x -=
              normalized_push.x * ENEMY_ENEMY_COLLISION_DISTANCE * delta;
          enemies[j].position.y -=
              normalized_push.y * ENEMY_ENEMY_COLLISION_DISTANCE * delta;
        }
      }
      /* Avoid stacking on player */
      Rectangle rect_player = {playerPosition.x, playerPosition.y,
                               SAFE_ZONE_DISTANCE, SAFE_ZONE_DISTANCE};
      if (CheckCollisionRecs(rect_i, rect_player)) {
        Vector2 push_direction =
            Vector2Subtract(enemy->position, playerPosition);
        if (push_direction.x == 0 && push_direction.y == 0) {
          push_direction.x = (float)(rand() % 100 - 50);
          push_direction.y = (float)(rand() % 100 - 50);
        }
        Vector2 normalized_push = Vector2Normalize(push_direction);

        enemy->position.x +=
            normalized_push.x * ENEMY_ENEMY_COLLISION_DISTANCE * delta;
        enemy->position.y +=
            normalized_push.y * ENEMY_ENEMY_COLLISION_DISTANCE * delta;
      }

      // Avoid stacking on player
      if (Vector2Length(direction) > safe_zone_distance) {
        direction = Vector2Normalize(direction);
        enemy->position.x += direction.x * delta * enemy->speed;
        enemy->position.y += direction.y * delta * enemy->speed;
      }

      if (enemy->hit_cooldown > 0) {
        enemy->hit_cooldown -= delta;
      }
      break;

    case ENEMY_TAKE_DEMAGE:
      enemy->timer += delta;

      // Generating pushback
      direction = Vector2Subtract(enemy->position, playerPosition);
      direction = Vector2Normalize(direction);
      enemy->position.x += direction.x * delta * enemy->exposed_force;
      enemy->position.y += direction.y * delta * enemy->exposed_force;

      if (enemy->timer >= enemy->stagger_duration) {
        *state = ENEMY_IDLE;
        enemy->timer = 0;
      }
      break;

    case ENEMY_DYING:
      enemy->timer += delta;
      if (enemy->timer >= enemy->dying_duration) {
        *state = ENEMY_DEAD;
        enemy->timer = 0;
      }
      break;
    case ENEMY_DEAD:
      enemy->timer += delta;
      if (enemy->timer >= enemy->dying_duration) {
        *enemy = GetEnemyProperties(enemy->sprite);
        *state = ENEMY_SPAWNING;
        enemy->position =
            GenerateSpawnPosition(map, playerPosition, enemy->spawn_distance);
        enemy->timer = 0;
      }
      break;
    }
  }
}

void DrawEnemies(EnemyData *enemy_data, bool is_paused, Rectangle camera_view) {
  Enemy *enemies = enemy_data->enemies;
  for (int i = 0; i < MAX_ENEMIES; i++) {
    if (enemy_data->state[i] == ENEMY_INACTIVE ||
        enemy_data->state[i] == ENEMY_DEAD) {
      continue;
    }
    // Reset animations if animations are switched
    if (enemies[i].last_state != enemy_data->state[i]) {
      enemies[i].animation.current_frame = 0;
    }
    PlayAnimation(enemies[i].hit_box, enemies[i].position,
                  &enemies[i].animation, enemies[i].sprite,
                  enemy_data->state[i], is_paused,
                  enemies[i].get_animation_data, camera_view);
    enemies[i].last_state = enemy_data->state[i];
  }
}
int GetClosestEnemy(EnemyData *enemy_data, Vector2 position) {
  Enemy *enemies = enemy_data->enemies;
  float closest_distance_sq = FLT_MAX;
  int closest_enemy_index = -1;

  for (int i = 0; i < MAX_ENEMIES; i++) {
    if (enemy_data->state[i] == ENEMY_WALKING ||
        enemy_data->state[i] == ENEMY_IDLE ||
        enemy_data->state[i] == ENEMY_TAKE_DEMAGE) {
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

void EnemyTakeDemage(EnemyData *enemy_data, const u64 index, const u64 demage) {

  Enemy enemy = enemy_data->enemies[index];
  EnemyState state = enemy_data->state[index];

  // enemy.exposed_force += force;
  state = ENEMY_TAKE_DEMAGE;
  enemy.health -= demage;

  /* Kill enemy */
  if (enemy.health <= 0) {
    state = ENEMY_DYING;
    SpawnOrb(enemy.position);
  }
}
