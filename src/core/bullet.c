
#include "core/bullet.h"
#include "core/camera.h"
#include "enemy/enemy.h"
#include "enemy/enemy_sprite.h"
#include "player/player.h"
#include <iso646.h>
#include <math.h>
#include <raylib.h>
#include <raymath.h>
#include <stdbool.h>

void InitBullets(Bullet *bullets) {
  for (int i = 0; i < MAX_BULLETS; i++) {
    bullets[i].active = false;
    bullets[i].last_hitted_enemy = -1;
    bullets[i].damage = 20;
  }
}

void FireBullet(Bullet *bullets, Player *player, float fireRate,
                bool is_auto_aim, EnemyData *enemy_data, GameCamera camera) {
  Vector2 playerPosition = player->position;
  Enemy *enemies = enemy_data->enemies;

  int pierce = 5;
  float range = 0.3f;
  for (int i = 0; i < MAX_BULLETS; i++) {
    if (!bullets[i].active) {
      bullets[i].position = playerPosition;
      bullets[i].size = (Vector2){10, 10};
      bullets[i].color = BLACK;
      bullets[i].force = 0;
      bullets[i].last_hitted_enemy = -1;
      Vector2 direction;

      if (is_auto_aim) {
        int closest_enemy = GetClosestEnemy(enemy_data, playerPosition);
        // No enemies active
        if (closest_enemy == -1) {
          return;
          // Aim closest_enemy
        } else {
          direction =
              Vector2Subtract(enemies[closest_enemy].position, playerPosition);
          if (direction.x > 0) {
            player->animation.is_facing_right = true;
          } else {
            player->animation.is_facing_right = false;
          }
        }
        // Manual aiming
      } else {
        Vector2 mouse_pos_world =
            GetScreenToWorld2D(GetMousePosition(), camera.properties);
        direction = Vector2Subtract(mouse_pos_world, playerPosition);
      }
      bullets[i].active = true;
      bullets[i].range = range;
      bullets[i].pierce = pierce;
      float length =
          sqrt(direction.x * direction.x + direction.y * direction.y);
      direction.x /= length;
      direction.y /= length;
      bullets[i].speed =
          (Vector2){direction.x * 2000.0f, direction.y * 2000.0f};
      break;
    }
  }
}

void UpdateBullets(Bullet *bullets, Map map) {
  float delta = GetFrameTime();
  for (int i = 0; i < MAX_BULLETS; i++) {
    if (bullets[i].active) {
      bullets[i].position.x += bullets[i].speed.x * delta;
      bullets[i].position.y += bullets[i].speed.y * delta;
      bullets[i].range -= delta;

      // Out of range
      if (bullets[i].range < 0.0f) {
        bullets[i].active = false;

        // Out of map
      } else if (bullets[i].position.x < 0 ||
                 bullets[i].position.x > map.width ||
                 bullets[i].position.y < 0 ||
                 bullets[i].position.y > map.height) {
        bullets[i].active = false;
      }
    }
  }
}

void DrawBullets(Bullet *bullets) {
  for (int i = 0; i < MAX_BULLETS; i++) {
    if (bullets[i].active) {
      DrawRectangleV(bullets[i].position, bullets[i].size, bullets[i].color);
    }
  }
}
void CheckBulletCollision(Bullet *bullets, EnemyData *enemy_data) {
  Enemy *enemies = enemy_data->enemies;
  float force = 9;

  for (int i = 0; i < MAX_BULLETS; i++) {
    Bullet *bullet = &bullets[i];
    if (bullets[i].active) {

      for (int j = 0; j < MAX_ENEMIES; j++) {
        Enemy *enemy = &enemy_data->enemies[j];
        EnemyState *enemy_state = &enemy_data->state[j];
        if (*enemy_state == ENEMY_WALKING) {
          if (CheckCollisionRecs(
                  (Rectangle){bullet->position.x, bullet->position.y,
                              bullet->size.x, bullet->size.y},
                  (Rectangle){enemy->position.x, enemy->position.y,
                              enemy->hit_box.x, enemy->hit_box.y})) {

            // If bullet has already hit this enemy, skip.
            if (bullet->last_hitted_enemy == j) {
              continue;
            }

            // Enemy is hit by bullet
            EnemyTakeDemage(enemy, enemy_state, bullet->damage);

            // Decrease bullet pierce
            bullet->last_hitted_enemy = j;
            bullet->pierce--;
            if (bullet->pierce <= 0) {
              bullet->active = false;
              break;
            }
          }
        }
      }
    }
  }
}
