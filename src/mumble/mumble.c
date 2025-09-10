
#include "mumble/mumble.h"
#include "enemy/enemy.h"
#include "mumble/mumble_sprite.h"
#include "player/player.h"
#include "raylib.h"

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

  /* Abstract data */
  MumbleState *mumble_states = mumble_data->state;
  Mumble *mumbles = mumble_data->mumbles;
  Vector2 player_position = player->position;
  Enemy *enemies = enemy_data->enemies;
  EnemyState *enemy_states = enemy_data->state;

  for (u16 i = 0; i < MAX_MUMBLES; i++) {
    if (mumble_states != MUMBLE_INACTIVE) {

      /* Mumble state mashine */
      switch (mumble_states[i]) {

      case CASTING_MUMBLE:
        mumbles[i].timer += delta;

        break;
      }
    }
  }
}
