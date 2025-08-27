
#include "bullet.h"
#include "enemy.h"
#include "player.h"
#include <iso646.h>
#include <math.h>
#include <raylib.h>
#include <raymath.h>

void InitBullets(Bullet *bullets) {
  for (int i = 0; i < MAX_BULLETS; i++) {
    bullets[i].active = false;
  }
}

void FireBullet(Bullet *bullets, Player *player, float fireRate,
                bool is_auto_aim, Enemy *enemies) {
  Vector2 playerPosition = player->position;

  float range = 0.3f;
  for (int i = 0; i < MAX_BULLETS; i++) {
    if (!bullets[i].active) {
      bullets[i].position = playerPosition;
      bullets[i].size = (Vector2){10, 10};
      bullets[i].color = BLACK;
      bullets[i].force = 0;
      Vector2 direction;

      if (is_auto_aim) {
        int closest_enemy = GetClosestEnemy(enemies, playerPosition);
        // No enemies avctive
        if (closest_enemy == 0) {
          return;
          // Aim closest_enemy
        } else {
          direction =
              Vector2Subtract(enemies[closest_enemy].position, playerPosition);
          if (direction.x > 0) {
            player->is_facing_right = true;
          } else {
            player->is_facing_right = false;
          }
        }
        // Manual aiming
      } else {
        Vector2 mouse_pos = GetMousePosition();
        direction = Vector2Subtract(
            (Vector2){mouse_pos.x * 2.0f, mouse_pos.y * 2.0f}, playerPosition);
      }
      bullets[i].range = range;
      bullets[i].active = true;
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
void CheckBulletCollision(Bullet *bullets, Enemy *enemies, Orb *orbs) {
  for (int i = 0; i < MAX_BULLETS; i++) {
    if (bullets[i].active) {
      for (int j = 0; j < MAX_ENEMIES; j++) {
        if (enemies[j].active &&
            CheckCollisionRecs(
                (Rectangle){bullets[i].position.x, bullets[i].position.y,
                            bullets[i].size.x, bullets[i].size.y},
                (Rectangle){enemies[j].position.x, enemies[j].position.y,
                            enemies[j].size.x, enemies[j].size.y})) {
          bullets[i].active = false;
          enemies[j].active = false;
          SpawnOrb(orbs, enemies[j].position);
        }
      }
    }
  }
}
