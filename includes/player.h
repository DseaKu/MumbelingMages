
#ifndef PLAYER_H
#define PLAYER_H

#include "animation_handler.h"
#include "enemy.h"
#include "map.h"
#include "raylib.h"
#include "sprite.h"

#define MAX_BULLETS 100

typedef struct Player {
  Animation animation;
  StateID state;
  SpriteID id;
  Vector2 position;
  Vector2 hit_box;
  Camera2D camera;
  float speed;
  float fireRate;
  float pickupRange;
  int health;
} Player;

Player InitPlayer(int screen_width, int screen_height);
void UpdatePlayer(Player *player, float fireTimer, bool is_auto_aim, Map map);
void DrawPlayer(Player player, bool is_pause);
void CheckPlayerCollision(Player *player, EnemyData *enemy_data);

#endif
