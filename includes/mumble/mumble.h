#ifndef MUMBLE_H
#define MUMBLE_H
#include "core/animation_handler.h"
#include "core/std_includes.h"
#include <raylib.h>

#define MAX_MUMBLES 20
typedef struct Mumble {
  Animation animation;
  Vector2 position;
  Vector2 speed;
  Vector2 hit_box;
  bool is_projectile;
  bool is_area;
  bool is_buff;
  bool is_debuff;
  u32 damage;
  u32 last_hitted_enemy;
  float range;
  GetAnimationDataFunc get_animation_data;
} Mumble;

typedef u8 MumbleState;

typedef struct MumbleData {
  Mumble mumbles[MAX_MUMBLES];
  MumbleState state[MAX_MUMBLES];
} MumbleData;

void InitMumble(MumbleData *mumble_data);

#endif // MUMBLE_H
