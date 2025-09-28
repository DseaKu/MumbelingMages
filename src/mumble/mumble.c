#include "mumble/mumble.h"
#include "enemy/enemy.h"
#include "mumble/mumble_properties.h"
#include "mumble/mumble_sprite.h"
#include "raylib.h"
#include "raymath.h"

void InitMumble(MumbleData *mumble_data) {}

void CastFireball(MumbleData *mumble_data) {
  u16 i = 0;
  /* Search for an empty mumble slot*/
  while (i < MAX_MUMBLES && mumble_data->state[i] != MUMBLE_INACTIVE) {
    i++;
  }
  Mumble *mumble = &mumble_data->mumbles[i];
  MumbleState *state = &mumble_data->state[i];

  *mumble = GetMumbleProperties(FIREBALL);
  *state = CASTING_MUMBLE;
}

void UpdateMumbles(MumbleData *mumble_data, const Vector2 casting_position,
                   EnemyData *enemy_data) {

  float delta = GetFrameTime();
  static u32 closest_enemy_index;
  Enemy *enemies = enemy_data->enemies;
  EnemyState *enemy_states = enemy_data->state;
  Vector2 direction;

  /* Could be changed, e.g. mouse position */
  Vector2 target_position =
      enemies[GetClosestEnemy(enemy_data, casting_position)].position;

  for (u16 i = 0; i < MAX_MUMBLES; i++) {
    if (mumble_data->state[i] != MUMBLE_INACTIVE) {
      Mumble *mumble = &mumble_data->mumbles[i];
      MumbleState *state = &mumble_data->state[i];

      /* Mumble state mashine */
      switch (*state) {

      case CASTING_MUMBLE:
        mumble->timer += delta;
        mumble->position = casting_position;
        if (mumble->timer >= mumble->casting_duration) {
          *state = MUMBLE_MOVE_TO_TARGET;
          mumble->timer = 0;
        }
        break;

      case MUMBLE_MOVE_TO_TARGET:
        direction = Vector2Subtract(target_position, mumble->position);
        direction = Vector2Normalize(direction);
        mumble->position = Vector2Add(
            mumble->position, Vector2Scale(direction, mumble->speed.x * delta));

        mumble->is_facing_right = (direction.x > 0);

        /* Check if colliding with closest enemy */
        closest_enemy_index = GetClosestEnemy(enemy_data, mumble->position);
        Enemy closest_enemy = enemies[closest_enemy_index];
        Rectangle rect_enemy = {
            closest_enemy.position.x, closest_enemy.position.y,
            closest_enemy.hit_box.x, closest_enemy.hit_box.y};
        Rectangle rect_mumble = {mumble->position.x, mumble->position.y,
                                 mumble->hit_box.x, mumble->hit_box.y};

        if (CheckCollisionRecs(rect_mumble, rect_enemy)) {
          *state = MUMBLE_HIT_TARGET;
        };
        break;

      case MUMBLE_HIT_TARGET:
        EnemyTakeDemage(&enemies[closest_enemy_index],
                        &enemy_states[closest_enemy_index], mumble->damage);
        *state = MUMBLE_INACTIVE;
        break;
      }
    }
  }
}
