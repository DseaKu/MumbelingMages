#ifndef ORB_H
#define ORB_H

#include "player/player.h"
#include "raylib.h"

#define MAX_ORBS MAX_ENEMIES

typedef struct Orb {
  Vector2 position;
  Vector2 size;
  Color color;
  bool active;
} Orb;

void InitOrbs(Orb *orbs);
void SpawnOrb(Orb *orbs, Vector2 position);
void UpdateOrbs(Orb *orbs);
void DrawOrbs(Orb *orbs);

void CheckOrbPickup(Player *player, Orb *orbs, int *exp);
#endif
