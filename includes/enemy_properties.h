#ifndef ENEMY_PROPERTIES_H
#define ENEMY_PROPERTIES_H

#include "enemy.h"
#include <raylib.h>

void LoadEnemyTextures(void);
void UnloadEnemyTextures(void);
Enemy GetEnemyProperties(EnemyID id);
Texture2D GetEnemyTexture(EnemyID id);

#endif // !ENEMY_PROPERTIES_H
