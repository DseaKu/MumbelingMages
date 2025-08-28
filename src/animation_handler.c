
#include "animation_handler.h"
#include "enemy.h"
static Texture2D enemy_textures[sizeof(EnemyID)][sizeof(AnimationID)];

void LoadEnemyTextures(void) {
  enemy_textures[GOBLIN][WALK] = LoadTexture("assets/Goblin/Run.png");
  // enemy_textures[SKELLETON] = LoadTexture("assets/Skeleton/Run.png");
  // enemy_textures[BAT] = LoadTexture("assets/Bat/Fly.png");
}

void LoadPlayerTextures(void) {
  enemy_textures[GOBLIN][WALK] = LoadTexture("assets/Goblin/Run.png");
  // enemy_textures[SKELLETON] = LoadTexture("assets/Skeleton/Run.png");
  // enemy_textures[BAT] = LoadTexture("assets/Bat/Fly.png");
}

void UnloadEnemyTextures(void) {
  for (int i = 0; i < sizeof(EnemyID); i++) {
    for (int j = 0; j < sizeof(AnimationID); j++) {
      // Make sure texture is valid before unloading
      if (enemy_textures[i][j].id > 0) {
        UnloadTexture(enemy_textures[i][j]);
      }
    }
  }
}

void UnloadPlayerTextures(void) {
  for (int i = 0; i < sizeof(EnemyID); i++) {
    for (int j = 0; j < sizeof(AnimationID); j++) {
      // Make sure texture is valid before unloading
      if (enemy_textures[i][j].id > 0) {
        UnloadTexture(enemy_textures[i][j]);
      }
    }
  }
}
Texture2D GetEnemyTexture(int enemy_id, int animation_id) {
  return enemy_textures[enemy_id][animation_id];
}
