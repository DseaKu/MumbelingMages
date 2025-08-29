#include "animation_handler.h"
#include "sprite.h"
#include <raylib.h>
static SpriteTexture sprite_textures[SIZE_SPRITE_ID][SIZE_STATE_ID];

void UpdateAnimation(Animation *animation, int sprite_id, int state_id) {
  SpriteTexture texture = GetTexture(sprite_id, state_id);
  animation->frame_timer += GetFrameTime();
  if (animation->frame_timer >= texture.frame_speed) {
    animation->frame_timer = 0.0f;
    animation->current_frame++;
    if (animation->current_frame >= texture.frame_count) {
      animation->current_frame = 0;
    }
  }
}

void PlayAnimation(Vector2 hit_box, Vector2 position, Animation *animation,
                   int sprite_id, int animation_id) {

  SpriteTexture texture = GetTexture(sprite_id, animation_id);
  UpdateAnimation(animation, sprite_id, animation_id);

  // Ger current frame from animation
  Rectangle sourceRec = {(float)animation->current_frame * texture.width, 0,
                         (float)texture.width, (float)texture.texture.height};

  // Animation face direction
  if (!animation->is_facing_right) {
    sourceRec.width *= -1;
  }

  // Calculate visual frame
  float visual_width = hit_box.x * texture.scale;
  float visual_heigth = hit_box.y * texture.scale;
  Rectangle destRec = {position.x, position.y, visual_width, visual_heigth};

  // Calculate offset of visual frame
  Vector2 origin = {visual_width / 2.0f, visual_heigth / 2.0f};

  DrawTexturePro(texture.texture, sourceRec, destRec, origin, 0, WHITE);
}

void LoadTextures(void) {
  // Mage
  sprite_textures[MAGE][WALK] =
      (SpriteTexture){LoadTexture("assets/mage.png"), 100, 100, 1, 2.0f};

  sprite_textures[GOBLIN][WALK] = (SpriteTexture){
      LoadTexture("assets/goblin/Run.png"), 150, 150, 8, 8.0f, 1.0f / 10.0f};
  sprite_textures[GOBLIN][TAKE_DEMAGE] = (SpriteTexture){
      LoadTexture("assets/goblin/Run.png"), 150, 150, 4, 8.0f, 1.0f / 10.0f};
}

void UnloadTextures(void) {
  for (int i = 0; i < SIZE_SPRITE_ID; i++) {
    for (int j = 0; j < SIZE_STATE_ID; j++) {
      UnloadTexture(sprite_textures[i][j].texture);
    }
  }
}

SpriteTexture GetTexture(int sprite_id, int animation_id) {

  // return textures[enemy_id][animation_id];
  return sprite_textures[sprite_id][animation_id];
}
