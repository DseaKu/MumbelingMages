#ifndef MAGE_TEXTURE_H
#define MAGE_TEXTURE_H

#include "animation_handler.h"
#include "mage/mage_sprite.h"
void LoadMageTextures(void);
void UnloadMageTextures(void);
AnimationData GetMageAnimationData(int sprite_id, int animation_id);
#endif // !MAGE_TEXTURE_H
