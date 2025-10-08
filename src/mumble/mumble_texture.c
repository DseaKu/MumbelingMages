#include "mumble/mumble_texture.h"
#include "core/animation_handler.h"
#include "mumble/mumble_sprite.h"
#include "raylib.h"
static AnimationData sprite_textures[SIZE_MUMBLE_SPRITE_ID]
                                    [SIZE_MUMBLE_STATE_ID];

void LoadMumbleTextures(void) {
  sprite_textures[FIREBALL][CASTING_MUMBLE] = (AnimationData){
      .texture = LoadTexture("assets/mumble/fireball/Casting.png"),
      .width = 64,
      .height = 64,
      .frame_count = 14,
      .scale = 8.0f,
      .frame_speed = 1.0f / 10.0f,
      .is_looping = true};

  sprite_textures[FIREBALL][MUMBLE_MOVE_TO_TARGET] = (AnimationData){
      .texture = LoadTexture("assets/mumble/fireball/IdleLoop.png"),
      .width = 64,
      .height = 64,
      .frame_count = 4,
      .scale = 8.0f,
      .frame_speed = 1.0f / 10.0f,
      .is_looping = true};
}

void UnloadMumbleTextures(void) {
  for (int i = 0; i < SIZE_MUMBLE_SPRITE_ID; i++) {
    for (int j = 0; j < SIZE_MUMBLE_STATE_ID; j++) {
      UnloadTexture(sprite_textures[i][j].texture);
    }
  }
}

AnimationData GetMumbleAnimationData(int sprite_id, int mumble_id) {
  return sprite_textures[sprite_id][mumble_id];
}
