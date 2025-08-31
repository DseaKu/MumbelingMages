#ifndef ENEMY_TEXTURE_H
#define ENEMY_TEXTURE_H
#include "animation_handler.h"
#include "enemy/enemy_sprite.h"

void LoadEnemyTextures(void);
void UnloadEnemyTextures(void);
AnimationData GetEnemyAnimationData(int sprite_id, int animation_id);
#endif // !ENEMY_TEXTURE_H
