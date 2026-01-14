#include "core/orb.h"
#include "raymath.h"
#include <raylib.h>

static Orb orbs[MAX_ORBS];

void InitOrbs() {
  for (int i = 0; i < MAX_ORBS; i++) {
    orbs[i].active = false;
  }
}

void SpawnOrb(Vector2 position) {
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

void UpdateOrbs() {
  // Orbs don't have any update logic for now
}

void DrawOrbs() {
  for (int i = 0; i < MAX_ORBS; i++) {
    if (orbs[i].active) {
      DrawRectangleV(orbs[i].position, orbs[i].size, orbs[i].color);
    }
  }
}
void CheckOrbPickup(Player *player, int *exp) {
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
