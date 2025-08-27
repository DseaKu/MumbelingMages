
#include "bullet.h"
#include "enemy.h"
#include "player.h"
#include "window.h"
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

  for (int i = 0; i < MAX_BULLETS; i++) {
    if (!bullets[i].active) {
      bullets[i].position = playerPosition;
      bullets[i].size = (Vector2){10, 10};
      bullets[i].color = BLACK;
      bullets[i].force = 0;
      Vector2 direction;

      if (is_auto_aim) {
        int closest_enemy = GetClosestEnemy(enemies, playerPosition);
        if (closest_enemy == 0) {
          return;
        } else {
          direction =
              Vector2Subtract(enemies[closest_enemy].position, playerPosition);
          if (direction.x > 0) {
            player->is_facing_right = true;
          } else {
            player->is_facing_right = false;
          }
        }
      } else {
        direction = Vector2Subtract(GetMousePosition(), playerPosition);
      }
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

      if (bullets[i].position.x < 0 || bullets[i].position.x > map.width ||
          bullets[i].position.y < 0 || bullets[i].position.y > map.height) {
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
