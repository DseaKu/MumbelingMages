
#ifndef PLAYER_H
#define PLAYER_H

#include "animation_handler.h"
#include "enemy/enemy.h"
#include "mage/mage_sprite.h"
#include "map.h"
#include "raylib.h"

#define MAX_BULLETS 100

typedef struct Player {
  Animation animation;
  MageStateID state;
  MageSpriteID id;
  Vector2 position;
  Vector2 hit_box;
  Camera2D camera;
  float speed;
  float fireRate;
  float pickupRange;
  int health;
  GetAnimationDataFunc get_animation_data;
} Player;

void InitPlayer(Player *player);
void UpdatePlayer(Player *player, float fireTimer, bool is_auto_aim, Map map);
void DrawPlayer(Player *player, bool is_pause);
void CheckPlayerCollision(Player *player, EnemyData *enemy_data);

#endif
