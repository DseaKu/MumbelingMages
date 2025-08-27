
#ifndef PLAYER_H
#define PLAYER_H

#include "enemy.h"
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
  int health;
  bool is_facing_right;
} Player;

Player InitPlayer();
void UpdatePlayer(Player *player, float fireTimer, bool is_auto_aim);
void DrawPlayer(Player player);
bool IsPlayerHit(Player player, Enemy *enemies, bool *game_over);

#endif
