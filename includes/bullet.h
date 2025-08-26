
#ifndef BULLET_H
#define BULLET_H

#include "raylib.h"

#define MAX_BULLETS 100

typedef struct Bullet {
    Vector2 position;
    Vector2 size;
    Color color;
    Vector2 speed;
    bool active;
} Bullet;

void InitBullets(Bullet *bullets);
void FireBullet(Bullet *bullets, Vector2 playerPosition, float fireTimer, float fireRate);
void UpdateBullets(Bullet *bullets);
void DrawBullets(Bullet *bullets);

#endif
