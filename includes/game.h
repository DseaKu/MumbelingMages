
#ifndef GAME_H
#define GAME_H

#include "IO_handler.h"
#include "bullet.h"
#include "enemy.h"
#include "map.h"
#include "orb.h"
#include "player.h"
#include "powerup.h"

void GameLoop();
void InitGame(Bullet *bullets, EnemyData *enemy_data, PowerUp *powerUps,
              Orb *orbs, int *exp, Map *map, IO_Flags *io_flags);
void DrawGame(Player player, Bullet *bullets, Enemy *enemies, PowerUp *powerUps,
              Orb *orbs, int exp, bool gameOver);

void CheckBulletCollision(Bullet *bullets, EnemyData *enemy_data, Orb *orbs);
void CheckOrbPickup(Player *player, Orb *orbs, int *exp);
void UnloadGame(Player player, Map map);
#endif
