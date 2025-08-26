
#ifndef GAME_H
#define GAME_H

#include "bullet.h"
#include "enemy.h"
#include "orb.h"
#include "player.h"
#include "powerup.h"

void GameLoop();
void InitGame(Bullet *bullets, Enemy *enemies, PowerUp *powerUps, Orb *orbs,
              int *exp, bool *gameOver);
void DrawGame(Player player, Bullet *bullets, Enemy *enemies, PowerUp *powerUps,
              Orb *orbs, int exp, bool gameOver, int screen_width,
              int screen_height);

void CheckBulletCollision(Bullet *bullets, Enemy *enemies, Orb *orbs);
void CheckOrbPickup(Player *player, Orb *orbs, int *exp);
void UnloadGame(Player player);
#endif
