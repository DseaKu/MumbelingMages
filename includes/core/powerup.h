#ifndef POWERUP_H
#define POWERUP_H

#include "player/player.h"
#include "raylib.h"

#define MAX_POWERUPS 5

typedef struct PowerUp {
  Vector2 position;
  Vector2 size;
  Color color;
  bool active;
} PowerUp;

void InitPowerUps(PowerUp *powerUps);
void SpawnPowerUp(PowerUp *powerUps);
void UpdatePowerUps(PowerUp *powerUps, Player *player);
void DrawPowerUps(PowerUp *powerUps);

#endif
