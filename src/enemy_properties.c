#include "enemy_properties.h"
#include "enemy.h"
#include "sprite.h"
static Enemy enemy_properties[SIZE_SPRITE_ID];

void LoadEnemyProperties() {
  enemy_properties[GOBLIN] = (Enemy){
      .sprite = GOBLIN,
      .health = 100,
      .spawn_duration = 1.0f,
      .stagger_duration = 0.5f,
      .dying_duration = 1.0f,
      .dead_duration = 1.0f,
      .spawn_distance = 10.0f,
      .speed = 900.0f,
      .hit_box = (Vector2){45, 45},
      .damage = 10,
      .attack_speed = 1.0f,
      .weight = 40.0f,
      .timer = 0.0f,

  };
}

Enemy GetEnemyProperties(int enemy_id) { return enemy_properties[enemy_id]; }
