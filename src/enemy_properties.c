#include "enemy_properties.h"
#include "enemy.h"

Enemy GetEnemyProperties(int enemy_id) {
  Enemy enemy;
  switch (enemy_id) {

  case GOBLIN:
    // Properties
    enemy.sprite = GOBLIN;
    enemy.health = 100;
    enemy.spawn_duration = 2.0f;
    enemy.stagger_duration = 0.5f;
    enemy.dying_duration = 2.0f;
    enemy.spawn_distance = 10.0f;
    enemy.speed = 200.0f;
    enemy.hit_box = (Vector2){45, 45};
    enemy.damage = 2;
    enemy.attack_speed = 1.0f;
    enemy.weight = 40.0f;
    enemy.timer = 0.0f;

    break;

  case SKELLETON:
    break;

  case BAT:
    break;

  default:
    break;
  }
  return enemy;
}
