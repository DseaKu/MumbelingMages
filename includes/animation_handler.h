#ifndef ANIMATION_HANDLER_H
#define ANIMATION_HANDLER_H

#include <raylib.h>

void LoadEnemyTextures(void);
void LoadPlayerTextures(void);
void UnloadEnemyTextures(void);
void UnloadPlayerTextures(void);
Texture2D GetEnemyTexture(int enemy_id, int animation_id);

#endif /* ifndef ANIMATION_HANDLER_H */
