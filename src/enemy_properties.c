#include "enemy_properties.h"
#include "enemy.h"

static Texture2D enemy_textures[ENEMY_ID_COUNT];

void LoadEnemyTextures(void) {
  enemy_textures[GOBLIN] = LoadTexture("assets/Goblin/Run.png");
  // enemy_textures[SKELLETON] = LoadTexture("assets/Skeleton/Run.png");
  // enemy_textures[BAT] = LoadTexture("assets/Bat/Fly.png");
}

void UnloadEnemyTextures(void) {
  for (int i = 0; i < ENEMY_ID_COUNT; i++) {
    // Make sure texture is valid before unloading
    if (enemy_textures[i].id > 0) {
      UnloadTexture(enemy_textures[i]);
    }
  }
}

Texture2D GetEnemyTexture(EnemyID id) { return enemy_textures[id]; }

Enemy GetEnemyProperties(EnemyID id) {
  Enemy enemy;
  switch (id) {

  case GOBLIN:
    // Properties
    enemy.health = 100;
    enemy.spawnTimer = 2.0f;
    enemy.spawn_distance = 10.0f;
    enemy.speed = 300.0f;
    enemy.size = (Vector2){45, 45};

    // Visual
    enemy.frameCount = 8;
    enemy.frameDuration = 1.0f / 12.0f;
    enemy.texture_scale = 8.0f;
    break;

  case SKELLETON:
    // Properties
    enemy.health = 100;
    enemy.spawnTimer = 2.0f;
    enemy.spawn_distance = 10.0f;
    enemy.speed = 200.0f;
    enemy.size = (Vector2){45, 45};

    // Visual
    enemy.frameCount = 8;
    enemy.frameDuration = 1.0f / 12.0f;
    enemy.texture_scale = 8.0f;
    break;

  case BAT:
    // Properties
    enemy.health = 100;
    enemy.spawnTimer = 2.0f;
    enemy.spawn_distance = 10.0f;
    enemy.speed = 200.0f;
    enemy.size = (Vector2){45, 45};

    // Visual
    enemy.frameCount = 1;
    enemy.frameDuration = 1.0f;
    enemy.texture_scale = 8.0f;
    break;

  case ENEMY_ID_COUNT:
    break;

  default:
    // Properties
    enemy.health = 100;
    enemy.spawnTimer = 2.0f;
    enemy.spawn_distance = 10.0f;
    enemy.speed = 200.0f;
    enemy.size = (Vector2){45, 45};

    // Visual
    enemy.frameCount = 1;
    enemy.frameDuration = 1.0f;
    enemy.texture_scale = 8.0f;
    break;
  }
  return enemy;
}
