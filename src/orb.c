#include "orb.h"
#include "raymath.h"
#include <raylib.h>

void InitOrbs(Orb *orbs) {
  for (int i = 0; i < MAX_ORBS; i++) {
    orbs[i].active = false;
  }
}

void SpawnOrb(Orb *orbs, Vector2 position) {
  for (int i = 0; i < MAX_ORBS; i++) {
    if (!orbs[i].active) {
      orbs[i].active = true;
      orbs[i].position = position;
      orbs[i].size = (Vector2){10, 10};
      orbs[i].color = YELLOW;
      break;
    }
  }
}

void UpdateOrbs(Orb *orbs) {
  // Orbs don't have any complex update logic for now
}

void DrawOrbs(Orb *orbs) {
  for (int i = 0; i < MAX_ORBS; i++) {
    if (orbs[i].active) {
      DrawRectangleV(orbs[i].position, orbs[i].size, orbs[i].color);
    }
  }
}
void CheckOrbPickup(Player *player, Orb *orbs, int *exp) {
  for (int i = 0; i < MAX_ORBS; i++) {
    if (orbs[i].active) {
      float distance = Vector2Distance(player->position, orbs[i].position);
      if (distance < player->pickupRange) {
        orbs[i].active = false;
        *exp += 10;
      }
    }
  }
}
