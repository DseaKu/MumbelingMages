
#include "enemy/enemy_texture.h"
#include "enemy/enemy_sprite.h"
static AnimationData sprite_textures[SIZE_SPRITE_ID][SIZE_STATE_ID];
void LoadEnemyTextures(void) {

  sprite_textures[GOBLIN][WALKING] = (AnimationData){
      LoadTexture("assets/goblin/Run.png"), 150, 150, 8, 8.0f, .1f, true};
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

void UnloadEnemyTextures(void) {
  for (int i = 0; i < SIZE_SPRITE_ID; i++) {
    for (int j = 0; j < SIZE_STATE_ID; j++) {
      UnloadTexture(sprite_textures[i][j].texture);
    }
  }
}

AnimationData GetEnemyAnimationData(int sprite_id, int animation_id) {
  return sprite_textures[sprite_id][animation_id];
}
