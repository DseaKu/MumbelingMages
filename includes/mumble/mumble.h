#ifndef MUMBLE_H
#define MUMBLE_H
#include "core/animation_handler.h"
#include <raylib.h>

typedef struct Spell {
  Animation animation;
  Vector2 position;
  Vector2 speed;
  Vector2 size;
  bool is_projectile;
  bool is_area;
  bool is_buff;
  bool is_debuff;

  GetAnimationDataFunc get_animation_data;
} Spell;
void InitSpells(Spell *spells);

#endif // MUMBLE_H
