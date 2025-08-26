
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
  float pickupRange;
  Texture2D texture;
} Player;

Player InitPlayer();
void UpdatePlayer(Player *player, float fireTimer, int screen_width,
                  int screen_height);
void DrawPlayer(Player player);

#endif
