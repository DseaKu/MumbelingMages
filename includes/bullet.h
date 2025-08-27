
#ifndef BULLET_H
#define BULLET_H

#include "enemy.h"
#include "orb.h"
#include "raylib.h"

#define MAX_BULLETS 100

typedef struct Bullet {
  Vector2 position;
  Vector2 size;
  Color color;
  Vector2 speed;
  bool active;
  int force;
  int pierce;
  int last_hitted_enemy;
  float range;
} Bullet;

void InitBullets(Bullet *bullets);
void FireBullet(Bullet *bullets, Player *player, float fireRate,
                bool is_auto_aim, Enemy *enemies);
void UpdateBullets(Bullet *bullets, Map map);
void DrawBullets(Bullet *bullets);
void CheckBulletCollision(Bullet *bullets, Enemy *enemies, Orb *orbs);

#endif
