#include "mage/mage_texture.h"

static AnimationData sprite_textures[SIZE_SPRITE_ID][SIZE_STATE_ID];
void LoadMageTextures(void) {
  // Mage
  sprite_textures[MAGE][WALKING] = (AnimationData){
      LoadTexture("assets/mage/Mage.png"), 400, 600, 7, 0.9f, 0.05f, true};
}

void UnloadMageTextures(void) {
  for (int i = 0; i < SIZE_SPRITE_ID; i++) {
    for (int j = 0; j < SIZE_STATE_ID; j++) {
      UnloadTexture(sprite_textures[i][j].texture);
    }
  }
}

AnimationData GetMageAnimationData(int sprite_id, int animation_id) {
  return sprite_textures[sprite_id][animation_id];
}
