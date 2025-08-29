#ifndef ANIMATION_HANDLER_H
#define ANIMATION_HANDLER_H

#include "sprite.h"
#include <raylib.h>
void LoadEnemyTextures(void);
void UnloadEnemyTextures(void);
Texture2D GetEnemyTexture(int enemy_id, int animation_id);

typedef struct SpriteTexture {
  Texture2D texture;
  int width;
  int height;
  int frame_count;
  float scale;
  float frame_speed;
} SpriteTexture;

typedef struct Animation {
  SpriteTexture texture;
  bool is_facing_right;
  int current_frame;
  float frame_timer;
} Animation;

void LoadTextures(void);
void UnloadTextures(void);
SpriteTexture GetTexture(int sprite_id, int animation_id);
void DrawSprite(Vector2 hit_box, Vector2 position, Animation *animation,
                int sprite_id, int state_id);
void UpdateAnimation(Animation *animation, int sprite_id, int state_id);

#endif /* ifndef ANIMATION_HANDLER_H */
