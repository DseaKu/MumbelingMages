#include "enemy_properties.h"
#include "animation_handler.h"
#include "enemy.h"

Enemy GetEnemyProperties(int enemy_id) {
  Enemy enemy;
  switch (enemy_id) {

  case GOBLIN:
    // Properties
    enemy.sprite = GOBLIN;
    enemy.health = 100;
    enemy.spawn_timer = 2.0f;
    enemy.spawn_distance = 10.0f;
    enemy.speed = 300.0f;
    enemy.hit_box = (Vector2){45, 45};
    enemy.damage = 10;
    enemy.attack_speed = 1.0f;

    break;

  case SKELLETON:
    // Properties
    enemy.sprite = SKELLETON;
    enemy.health = 100;
    enemy.spawn_timer = 2.0f;
    enemy.spawn_distance = 10.0f;
    enemy.speed = 200.0f;
    enemy.hit_box = (Vector2){45, 45};
    enemy.damage = 10;
    enemy.attack_speed = 1.0f;
    break;

  case BAT:
    // Properties
    enemy.sprite = BAT;
    enemy.health = 100;
    enemy.spawn_timer = 2.0f;
    enemy.spawn_distance = 10.0f;
    enemy.speed = 200.0f;
    enemy.hit_box = (Vector2){45, 45};
    enemy.damage = 10;
    enemy.attack_speed = 1.0f;

    break;

  default:
    // Properties
    enemy.sprite = NONE;
    enemy.health = 100;
    enemy.spawn_timer = 2.0f;
    enemy.spawn_distance = 10.0f;
    enemy.speed = 200.0f;
    enemy.hit_box = (Vector2){45, 45};
    enemy.damage = 10;
    enemy.attack_speed = 1.0f;

    break;
  }
  return enemy;
}
