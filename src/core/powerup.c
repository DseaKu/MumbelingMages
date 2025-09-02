
#include "core/powerup.h"
#include "core/player.h"
#include "raymath.h"
#include <stdlib.h>

void InitPowerUps(PowerUp *powerUps) {
  for (int i = 0; i < MAX_POWERUPS; i++) {
    powerUps[i].active = false;
  }
}

void SpawnPowerUp(PowerUp *powerUps) {
  for (int i = 0; i < MAX_POWERUPS; i++) {
    if (!powerUps[i].active) {
      powerUps[i].active = true;
      powerUps[i].position =
          (Vector2){rand() % (800 - 40) + 20, rand() % (450 - 40) + 20};
      powerUps[i].size = (Vector2){20, 20};
      powerUps[i].color = GREEN;
      break;
    }
  }
}

void UpdatePowerUps(PowerUp *powerUps, Player *player) {
  for (int i = 0; i < MAX_POWERUPS; i++) {
    if (powerUps[i].active) {
      float distance = Vector2Distance(player->position, powerUps[i].position);
      if (distance < player->pickupRange) {
        powerUps[i].active = false;
        player->fireRate *= 0.55f;
      }
    }
  }
}

void DrawPowerUps(PowerUp *powerUps) {
  for (int i = 0; i < MAX_POWERUPS; i++) {
    if (powerUps[i].active) {
      DrawRectangleV(powerUps[i].position, powerUps[i].size, powerUps[i].color);
    }
  }
}
