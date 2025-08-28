
#ifndef ENEMY_H
#define ENEMY_H

#include "map.h"
#include "raylib.h"

#define MAX_ENEMIES 20
typedef enum { GOBLIN = 0, SKELLETON, BAT } EnemyID;
typedef enum {
  WALK = 1 << 0,
  Idle = 1 << 1,
  IS_HITTED = 1 << 2,
  DEAD = 1 << 3,
} AnimationID;

typedef struct Enemy {
  EnemyID id;
  Vector2 position;
  Vector2 size;
  Color color;
  bool active;
  bool spawning;
  bool is_hit;
  bool is_facing_right;

  // Properties
  float speed;
  float spawnTimer;
  float spawn_distance;
  int health;
  int damage;
  float hit_cooldown;
  float attack_speed;

  // Visual
  AnimationID anmimation_id;
  int currentFrame;
  int frameCount;
  float frameTimer;
  float frameDuration;
  float texture_scale;

} Enemy;

void InitEnemies(Enemy *enemies);
void SpawnEnemy(Enemy *enemies, Map map, Vector2 player_position);
void UpdateEnemies(Enemy *enemies, Vector2 playerPosition);
void DrawEnemies(Enemy *enemies);
int GetClosestEnemy(Enemy *enemies, Vector2 position);

#endif
