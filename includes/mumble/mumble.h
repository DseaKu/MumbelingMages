#ifndef SPELL_H
#define SPELL_H
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

} Spell;

void InitSpells(Spell *spells);

#endif
