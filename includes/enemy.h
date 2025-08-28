
#ifndef ENEMY_H
#define ENEMY_H
#include "animation_handler.h"

#include "map.h"
#include "raylib.h"
#include "sprite.h"

#define MAX_ENEMIES 2

typedef struct DynamicPath {
  bool is_active;
  bool keep_face_dir;
  Vector2 target;
  float tmp_speed;
  float duration;

} DynamicPath;

typedef struct Enemy {
  SpriteID sprite;
  StateID state;
  DynamicPath dynamic_path;
  Vector2 position;
  Color color;
  bool active;

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

void InitEnemies(Enemy *enemies);
void SpawnEnemy(Enemy *enemies, Map map, Vector2 player_position);
void UpdateEnemies(Enemy *enemies, Vector2 playerPosition);
void DrawEnemies(Enemy *enemies);
int GetClosestEnemy(Enemy *enemies, Vector2 position);

#endif
