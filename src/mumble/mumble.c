
#include "mumble/mumble.h"
#include "enemy/enemy.h"
#include "mumble/mumble_sprite.h"
#include "player/player.h"
#include "raylib.h"
#include "raymath.h"

void InitMumble(MumbleData *mumble_data) {}

void CastFireball(MumbleData *mumble_data) {
  u16 index = 0;
  /* Search for an empty mumble slot*/
  while (index < MAX_MUMBLES && mumble_data->state[index] != MUMBLE_INACTIVE) {
    index++;
  }
  mumble_data->mumbles[index].id = FIREBALL;
  mumble_data->state[index] = CASTING_MUMBLE;
}

void UpdateMumbles(MumbleData *mumble_data, Player *player,
                   EnemyData *enemy_data) {

  float delta = GetFrameTime();
  Vector2 player_position = player->position;
  Enemy *enemies = enemy_data->enemies;
  EnemyState *enemy_states = enemy_data->state;
  Vector2 direction;

  /* Could be changed, e.g. mouse position */
  Vector2 target_position =
      enemies[GetClosestEnemy(enemy_data, player_position)].position;

  for (u16 i = 0; i < MAX_MUMBLES; i++) {
    if (mumble_data->state[i] != MUMBLE_INACTIVE) {
      Mumble mumble = mumble_data->mumbles[i];
      MumbleState mumble_state = mumble_data->state[i];

      /* Mumble state mashine */
      switch (mumble_state) {

      case CASTING_MUMBLE:
        mumble.timer += delta;
        mumble.position = player_position;
        if (mumble.timer >= mumble.casting_duration) {
          mumble_state = MUMBLE_MOVE_TO_TARGET;
          mumble.timer = 0;
        }
        break;

      case MUMBLE_MOVE_TO_TARGET:
        direction = Vector2Subtract(mumble.position, target_position);
        mumble.is_facing_right = (direction.x > 0);

        /* Check if colliding with closest enemy */
        Enemy closest_enemy =
            enemies[GetClosestEnemy(enemy_data, mumble.position)];
        Rectangle rect_enemy = {
            closest_enemy.position.x, closest_enemy.position.y,
            closest_enemy.hit_box.x, closest_enemy.hit_box.y};
        Rectangle rect_mumble = {mumble.position.x, mumble.position.y,
                                 mumble.hit_box.x, mumble.hit_box.y};
        if (CheckCollisionRecs(rect_mumble, rect_enemy)) {
        }

        break;
      }
    }
  }
}
