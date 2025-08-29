
#ifndef ENEMY_H
#define ENEMY_H
#include "animation_handler.h"

#include "map.h"
#include "raylib.h"
#include "sprite.h"
#include "std_includes.h"

#define MAX_ENEMIES 20

typedef struct DynamicPath {
  bool is_active;
  bool keep_face_dir;
  Vector2 target;
  float tmp_speed;
  float duration;

} DynamicPath;

typedef struct Enemy {
  SpriteID sprite;
  DynamicPath dynamic_path;
  Vector2 position;
  Color color;

  // Properties
  Vector2 hit_box;
  float speed;
  float spawn_timer;
  float spawn_distance;
  int health;
  int damage;
  float hit_cooldown;
  float attack_speed;

  // Visual
  Animation animation;

} Enemy;

typedef u8 EnemyState;

typedef struct EnemyData {
  Enemy enemies[MAX_ENEMIES];
  EnemyState state[MAX_ENEMIES];
} EnemyData;

void InitEnemies(EnemyData *enemy_data);
void SpawnEnemy(EnemyData *enemy_data, Map map, Vector2 player_position);
void UpdateEnemies(EnemyData *enemy_data, Vector2 playerPosition);
void DrawEnemies(EnemyData *enemy_data);
int GetClosestEnemy(EnemyData *enemy_data, Vector2 position);

#endif
