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

void InitOrbs();
void SpawnOrb(Vector2 position);
void UpdateOrbs();
void DrawOrbs();

void CheckOrbPickup(Player *player, int *exp);
#endif
