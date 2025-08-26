
#ifndef GAME_H
#define GAME_H

#include "bullet.h"
#include "enemy.h"
#include "player.h"
#include "powerup.h"

void GameLoop();
void InitGame(Bullet *bullets, Enemy *enemies, PowerUp *powerUps, int *score,
              bool *gameOver);
void DrawGame(Player player, Bullet *bullets, Enemy *enemies, PowerUp *powerUps,
              int score, bool gameOver);

void CheckBulletCollision(Bullet *bullets, Enemy *enemies, int *score);
#endif
