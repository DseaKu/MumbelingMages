
#ifndef ENEMY_H
#define ENEMY_H
#include "animation_handler.h"

#include "map.h"
#include "raylib.h"
#include "sprite.h"

<<<<<<< HEAD
#define MAX_ENEMIES 20
typedef enum { GOBLIN = 0, SKELLETON, BAT } EnemyID;
typedef enum {
  WALK = 1 << 0,
  Idle = 1 << 1,
  IS_HITTED = 1 << 2,
  DEAD = 1 << 3,
} AnimationID;
=======
#define MAX_ENEMIES 2

typedef struct DynamicPath {
  bool is_active;
  bool keep_face_dir;
  Vector2 target;
  float tmp_speed;
  float duration;

} DynamicPath;
>>>>>>> @{-1}

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
<<<<<<< HEAD
  AnimationID anmimation_id;
  int currentFrame;
  int frameCount;
  float frameTimer;
  float frameDuration;
  float texture_scale;
=======
  Animation animation;
>>>>>>> @{-1}

} Enemy;

void InitEnemies(Enemy *enemies);
void SpawnEnemy(Enemy *enemies, Map map, Vector2 player_position);
void UpdateEnemies(Enemy *enemies, Vector2 playerPosition);
void DrawEnemies(Enemy *enemies);
int GetClosestEnemy(Enemy *enemies, Vector2 position);

#endif
