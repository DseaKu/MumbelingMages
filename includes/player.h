
#ifndef PLAYER_H
#define PLAYER_H

#include "animation_handler.h"
#include "enemy.h"
#include "map.h"
#include "raylib.h"

#define MAX_BULLETS 100

typedef struct Player {
  Vector2 position;
  Color color;

  // Properties
  Vector2 size;
  float speed;
  float fireRate;
  float pickupRange;
  int health;

  // Visual
  StateID anmimation_id;
  Animation animation;
  Texture2D texture;
  bool is_facing_right;
  Camera2D camera;
  int currentFrame;
  int frameCount;
  float texture_scale;
} Player;

Player InitPlayer(int screen_width, int screen_height);
void UpdatePlayer(Player *player, float fireTimer, bool is_auto_aim, Map map);
void DrawPlayer(Player player);
void CheckPlayerCollision(Player *player, Enemy *enemies);

#endif
