
#include "enemy/enemy_texture.h"
#include "enemy/enemy_sprite.h"
static AnimationData sprite_textures[SIZE_ENEMY_SPRITE_ID][SIZE_ENEMY_STATE_ID];
void LoadEnemyTextures(void) {

  sprite_textures[GOBLIN][ENEMY_WALKING] = (AnimationData){
      LoadTexture("assets/enemy/goblin/Run.png"), 150, 150, 8, 8.0f, .1f, true};
  sprite_textures[GOBLIN][ENEMY_TAKE_DEMAGE] =
      (AnimationData){LoadTexture("assets/enemy/goblin/Take Hit.png"),
                      150,
                      150,
                      4,
                      8.0f,
                      1.0f / 10.0f,
                      false};
  sprite_textures[GOBLIN][ENEMY_SPAWNING] =
      (AnimationData){LoadTexture("assets/enemy/goblin/Idle.png"),
                      150,
                      150,
                      4,
                      8.0f,
                      1.0f / 10.0f,
                      false};
  sprite_textures[GOBLIN][ENEMY_IDLE] =
      (AnimationData){LoadTexture("assets/enemy/goblin/Idle.png"),
                      150,
                      150,
                      4,
                      8.0f,
                      1.0f / 10.0f,
                      true};
  sprite_textures[GOBLIN][ENEMY_DYING] =
      (AnimationData){LoadTexture("assets/enemy/goblin/Death.png"),
                      150,
                      150,
                      4,
                      8.0f,
                      1.0f / 10.0f,
                      false};
}

void UnloadEnemyTextures(void) {
  for (int i = 0; i < SIZE_ENEMY_SPRITE_ID; i++) {
    for (int j = 0; j < SIZE_ENEMY_STATE_ID; j++) {
      UnloadTexture(sprite_textures[i][j].texture);
    }
  }
}

AnimationData GetEnemyAnimationData(int sprite_id, int animation_id) {
  return sprite_textures[sprite_id][animation_id];
}
