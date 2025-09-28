
#ifndef GAME_H
#define GAME_H

#include "core/IO_handler.h"
#include "core/bullet.h"
#include "core/camera.h"
#include "core/map.h"
#include "core/orb.h"
#include "core/powerup.h"
#include "enemy/enemy.h"
#include "mumble/mumble.h"
#include "player/player.h"

void GameLoop();
void InitGame(Bullet *bullets, EnemyData *enemy_data, MumbleData *mumble_data,
              PowerUp *powerUps, int *exp, Map *map, IO_Flags *io_flags,
              Player *player, GameCamera *camera);
void DrawGame(Player player, Bullet *bullets, Enemy *enemies, PowerUp *powerUps,
              Orb *orbs, int exp, bool gameOver);

// void CheckBulletCollision(Bullet *bullets, EnemyData *enemy_data);
void CheckOrbPickup(Player *player, int *exp);
void UnloadGame(Player player, Map map);
#endif
