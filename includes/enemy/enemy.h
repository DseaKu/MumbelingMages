
#ifndef ENEMY_H
#define ENEMY_H
#include "core/animation_handler.h"
#include "core/map.h"
#include "core/std_includes.h"
#include "enemy/enemy_sprite.h"
#include "raylib.h"

#define MAX_ENEMIES 30
#define ENEMY_ENEMY_COLLISION_DISTANCE 100.0f

typedef struct DynamicPath {
  bool is_active;
  bool keep_face_dir;
  Vector2 target;
  float tmp_speed;
  float duration;

} DynamicPath;

typedef struct Enemy {
  Animation animation;
  EnemySpriteID id;
  DynamicPath dynamic_path;
  Vector2 position;
  Vector2 hit_box;
  u8 last_state;
  u16 damage;
  s64 health;
  float exposed_force;
  float weight;
  float speed;
  float spawn_duration;
  float stagger_duration;
  float dying_duration;
  float dead_duration;
  float timer;
  float spawn_distance;
  float hit_cooldown;
  float attack_speed;
  GetAnimationDataFunc get_animation_data;
} Enemy;

typedef u8 EnemyState;

typedef struct EnemyData {
  Enemy enemies[MAX_ENEMIES];
  EnemyState state[MAX_ENEMIES];
} EnemyData;

void InitEnemies(EnemyData *enemy_data);
void SpawnEnemy(EnemyData *enemy_data, Map map, Vector2 player_position);

Vector2 GenerateSpawnPosition(Map map, Vector2 player_position,
                              float spawn_distance);
void UpdateEnemies(EnemyData *enemy_data, Vector2 playerPosition, Map map);
void DrawEnemies(EnemyData *enemy_data, bool is_pause, Rectangle camera_view);
int GetClosestEnemy(EnemyData *enemy_data, Vector2 position);
void EnemyTakeDemage(Enemy *enemy, EnemyState *state, const u64 damage);

#endif
