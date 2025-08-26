
#include "bullet.h"
#include <math.h>
#include <raylib.h>

void InitBullets(Bullet *bullets) {
  for (int i = 0; i < MAX_BULLETS; i++) {
    bullets[i].active = false;
  }
}

void FireBullet(Bullet *bullets, Vector2 playerPosition, float fireTimer,
                float fireRate) {
  if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && fireTimer >= fireRate) {
    for (int i = 0; i < MAX_BULLETS; i++) {
      if (!bullets[i].active) {
        bullets[i].active = true;
        bullets[i].position = playerPosition;
        bullets[i].size = (Vector2){10, 10};
        bullets[i].color = BLACK;
        Vector2 mousePos = GetMousePosition();
        Vector2 direction = {mousePos.x - playerPosition.x,
                             mousePos.y - playerPosition.y};
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
}

void UpdateBullets(Bullet *bullets) {
  float delta = GetFrameTime();
  for (int i = 0; i < MAX_BULLETS; i++) {
    if (bullets[i].active) {
      bullets[i].position.x += bullets[i].speed.x * delta;
      bullets[i].position.y += bullets[i].speed.y * delta;

      if (bullets[i].position.x < 0 || bullets[i].position.x > 800 ||
          bullets[i].position.y < 0 || bullets[i].position.y > 450) {
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
