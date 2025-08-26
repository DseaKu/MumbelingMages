
#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

#define MAX_BULLETS 100

typedef struct Player {
  Vector2 position;
  Vector2 size;
  Color color;
  float speed;
  float fireRate;
} Player;

Player InitPlayer();
void UpdatePlayer(Player *player, float fireTimer);
void DrawPlayer(Player player);

#endif
