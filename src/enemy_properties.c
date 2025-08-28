#include "enemy_properties.h"
#include "enemy.h"

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
    enemy.damage = 10;
    enemy.attack_speed = 1.0f;

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
    enemy.damage = 10;
    enemy.attack_speed = 1.0f;

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
    enemy.damage = 10;
    enemy.attack_speed = 1.0f;

    // Visual
    enemy.frameCount = 1;
    enemy.frameDuration = 1.0f;
    enemy.texture_scale = 8.0f;
    break;

  default:
    // Properties
    enemy.health = 100;
    enemy.spawnTimer = 2.0f;
    enemy.spawn_distance = 10.0f;
    enemy.speed = 200.0f;
    enemy.size = (Vector2){45, 45};
    enemy.damage = 10;
    enemy.attack_speed = 1.0f;

    // Visual
    enemy.frameCount = 1;
    enemy.frameDuration = 1.0f;
    enemy.texture_scale = 8.0f;
    break;
  }
  return enemy;
}
