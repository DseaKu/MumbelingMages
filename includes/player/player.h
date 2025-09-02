
#ifndef PLAYER_H
#define PLAYER_H

#include "core/animation_handler.h"
#include "core/map.h"
#include "enemy/enemy.h"
#include "player/player_sprite.h"
#include "raylib.h"

#define MAX_BULLETS 100
#define SAFE_ZONE_DISTANCE 75.0f

typedef struct Player {
  Animation animation;
  PlayerStateID state;
  PlayerSpriteID id;
  Vector2 position;
  Vector2 hit_box;
  float speed;
  float fireRate;
  float pickupRange;
  int health;
  GetAnimationDataFunc get_animation_data;
} Player;

void InitPlayer(Player *player);
void UpdatePlayer(Player *player, float fireTimer, bool is_auto_aim, Map map);
void DrawPlayer(Player *player, bool is_pause, Rectangle camera_view);
void CheckPlayerCollision(Player *player, EnemyData *enemy_data);

#endif
