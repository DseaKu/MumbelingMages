#ifndef ANIMATION_HANDLER_H
#define ANIMATION_HANDLER_H
#include <raylib.h>

typedef struct AnimationData {
  Texture2D texture;
  int width;
  int height;
  int frame_count;
  float scale;
  float frame_speed;
  bool is_looping;
} AnimationData;

typedef struct Animation {
  bool is_facing_right;
  int current_frame;
  float frame_timer;

} Animation;

typedef AnimationData (*GetAnimationDataFunc)(int, int);

void PlayAnimation(Vector2 hit_box, Vector2 position, Animation *animation,
                   int sprite_id, int animation_id, bool is_pause,
                   GetAnimationDataFunc get_animation_data);
void UpdateAnimation(AnimationData animation_data, Animation *animation,
                     int sprite_id, int state_id);

#endif /* ifndef ANIMATION_HANDLER_H */
