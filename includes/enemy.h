
#ifndef ENEMY_H
#define ENEMY_H

#include "map.h"
#include "raylib.h"

#define MAX_ENEMIES 20

typedef struct Enemy {
  Vector2 position;
  Vector2 size;
  Color color;
  bool active;
  bool spawning;
  float speed;
  float spawnTimer;
} Enemy;

void InitEnemies(Enemy *enemies);
void SpawnEnemy(Enemy *enemies, Map map);
void UpdateEnemies(Enemy *enemies, Vector2 playerPosition);
void DrawEnemies(Enemy *enemies);
int GetClosestEnemy(Enemy *enemies, Vector2 position);

#endif
