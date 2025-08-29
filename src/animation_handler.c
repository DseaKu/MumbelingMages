#include "animation_handler.h"
#include "sprite.h"
#include <raylib.h>
#include <stdbool.h>
static AnimationData sprite_textures[SIZE_SPRITE_ID][SIZE_STATE_ID];

void UpdateAnimation(AnimationData animation_data, Animation *animation,
                     int sprite_id, int state_id) {
  animation->frame_timer += GetFrameTime();
  if (animation->frame_timer >= animation_data.frame_speed) {
    animation->frame_timer = 0.0f;
    animation->current_frame++;
    if (animation->current_frame >= animation_data.frame_count) {
      if (animation_data.is_looping) {
        animation->current_frame = 0;
      } else {
        animation->current_frame = animation_data.frame_count - 1;
      }
    }
  }
}

void PlayAnimation(Vector2 hit_box, Vector2 position, Animation *animation,
                   int sprite_id, int animation_id, bool is_paused) {

  AnimationData animation_data = GetAnimationData(sprite_id, animation_id);
  if (!is_paused) {
    UpdateAnimation(animation_data, animation, sprite_id, animation_id);
  }

  // Get current frame from animation
  Rectangle sourceRec = {(float)animation->current_frame * animation_data.width,
                         0, (float)animation_data.width,
                         (float)animation_data.texture.height};

  // Animation face direction
  if (!animation->is_facing_right) {
    sourceRec.width *= -1;
  }

  // Calculate visual frame
  float visual_width = hit_box.x * animation_data.scale;
  float visual_heigth = hit_box.y * animation_data.scale;
  Rectangle destRec = {position.x, position.y, visual_width, visual_heigth};

  // Calculate offset of visual frame
  Vector2 origin = {visual_width / 2.0f, visual_heigth / 2.0f};

  DrawTexturePro(animation_data.texture, sourceRec, destRec, origin, 0, WHITE);
}

void LoadTextures(void) {
  // Mage
  sprite_textures[MAGE][WALKING] = (AnimationData){
      LoadTexture("assets/mage.png"), 100, 100, 1, 2.0f, 0.1f, true};

  sprite_textures[GOBLIN][WALKING] =
      (AnimationData){LoadTexture("assets/goblin/Run.png"),
                      150,
                      150,
                      8,
                      8.0f,
                      1.0f / 10.0f,
                      true};
  sprite_textures[GOBLIN][TAKE_DEMAGE] =
      (AnimationData){LoadTexture("assets/goblin/Take Hit.png"),
                      150,
                      150,
                      4,
                      8.0f,
                      1.0f / 10.0f,
                      false};
  sprite_textures[GOBLIN][SPAWNING] =
      (AnimationData){LoadTexture("assets/goblin/Idle.png"),
                      150,
                      150,
                      4,
                      8.0f,
                      1.0f / 10.0f,
                      false};
  sprite_textures[GOBLIN][IDLE] =
      (AnimationData){LoadTexture("assets/goblin/Idle.png"),
                      150,
                      150,
                      4,
                      8.0f,
                      1.0f / 10.0f,
                      true};
  sprite_textures[GOBLIN][DYING] =
      (AnimationData){LoadTexture("assets/goblin/Death.png"),
                      150,
                      150,
                      4,
                      8.0f,
                      1.0f / 10.0f,
                      false};
}

void UnloadTextures(void) {
  for (int i = 0; i < SIZE_SPRITE_ID; i++) {
    for (int j = 0; j < SIZE_STATE_ID; j++) {
      UnloadTexture(sprite_textures[i][j].texture);
    }
  }
}

AnimationData GetAnimationData(int sprite_id, int animation_id) {

  // return textures[enemy_id][animation_id];
  return sprite_textures[sprite_id][animation_id];
}
