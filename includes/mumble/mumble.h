#ifndef MUMBLE_H
#define MUMBLE_H
#include "core/animation_handler.h"
#include "core/std_includes.h"
#include "enemy/enemy.h"
#include "mumble/mumble_sprite.h"
#include <raylib.h>

#define MAX_MUMBLES 40
typedef struct Mumble {
  MumbleSpriteID id;
  Animation animation;
  Vector2 position;
  Vector2 speed;
  Vector2 hit_box;
  bool is_projectile;
  bool is_area;
  bool is_buff;
  bool is_debuff;
  bool is_facing_right;
  u32 damage;
  u32 last_hitted_enemy;
  float range;
  float timer;
  float casting_duration;
  GetAnimationDataFunc get_animation_data;
} Mumble;

typedef u8 MumbleState;

typedef struct MumbleData {
  Mumble mumbles[MAX_MUMBLES];
  MumbleState state[MAX_MUMBLES];
} MumbleData;

void InitMumble(MumbleData *mumble_data);
void CastFireball(MumbleData *mumble_data);
void UpdateMumbles(MumbleData *mumble_data, const Vector2 casting_position,
                   EnemyData *enemy_data);

#endif // MUMBLE_H
