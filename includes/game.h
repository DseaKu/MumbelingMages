
#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "powerup.h"

void InitGame(Player *player, Bullet *bullets, Enemy *enemies, PowerUp *powerUps, int *score, bool *gameOver);
void UpdateGame(Player *player, Bullet *bullets, Enemy *enemies, PowerUp *powerUps, int *score, bool *gameOver, float *fireTimer, float *enemySpawnTimer, float *powerUpSpawnTimer);
void DrawGame(Player player, Bullet *bullets, Enemy *enemies, PowerUp *powerUps, int score, bool gameOver);

#endif
