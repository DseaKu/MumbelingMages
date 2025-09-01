#include "mage/mage_texture.h"
#include "mage/mage_sprite.h"

static AnimationData sprite_textures[SIZE_MAGE_SPRITE_ID][SIZE_MAGE_STATE_ID];
void LoadMageTextures(void) {
  // Mage
  sprite_textures[MAGE][MAGE_WALKING] = (AnimationData){
      LoadTexture("assets/mage/Mage.png"), 400, 600, 7, 0.9f, 0.05f, true};
}

void UnloadMageTextures(void) {
  // for (int i = 0; i < SIZE_SPRITE_ID; i++) {
  //   for (int j = 0; j < SIZE_STATE_ID; j++) {
  for (int i = 0; i < SIZE_MAGE_SPRITE_ID; i++) {
    for (int j = 0; j < SIZE_MAGE_STATE_ID; j++) {
      UnloadTexture(sprite_textures[i][j].texture);
    }
  }
}

AnimationData GetMageAnimationData(int mage_id, int animation_id) {
  return sprite_textures[mage_id][animation_id];
}
