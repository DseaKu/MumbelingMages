
#ifndef GAME_H
#define GAME_H

#include "core/IO_handler.h"
#include "core/bullet.h"
#include "core/map.h"
#include "core/orb.h"
#include "core/powerup.h"
#include "enemy/enemy.h"
#include "player.h"
#include "raylib.h"

void GameLoop();
void InitGame(Bullet *bullets, EnemyData *enemy_data, PowerUp *powerUps,
              Orb *orbs, int *exp, Map *map, IO_Flags *io_flags, Player *player,
              Camera2D *camera);
void DrawGame(Player player, Bullet *bullets, Enemy *enemies, PowerUp *powerUps,
              Orb *orbs, int exp, bool gameOver);

void CheckBulletCollision(Bullet *bullets, EnemyData *enemy_data, Orb *orbs);
void CheckOrbPickup(Player *player, Orb *orbs, int *exp);
void UnloadGame(Player player, Map map);
#endif
