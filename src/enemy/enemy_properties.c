#include "enemy/enemy_properties.h"
#include "enemy/enemy.h"
#include "enemy/enemy_sprite.h"
#include "enemy/enemy_texture.h"
static Enemy enemy_properties[SIZE_ENEMY_SPRITE_ID];

void LoadEnemyProperties() {
  enemy_properties[GOBLIN] = (Enemy){
      .id = GOBLIN,
      .health = 100,
      .spawn_duration = 1.0f,
      .stagger_duration = 0.5f,
      .dying_duration = 1.0f,
      .dead_duration = 1.0f,
      .spawn_distance = 10.0f,
      .speed = 300.0f,
      .hit_box = (Vector2){45, 45},
      .damage = 10,
      .attack_speed = 1.0f,
      .weight = 40.0f,
      .timer = 0.0f,
      .get_animation_data = GetEnemyAnimationData,

  };
}

Enemy GetEnemyProperties(int enemy_id) { return enemy_properties[enemy_id]; }
