#ifndef MAGE_TEXTURE_H
#define MAGE_TEXTURE_H

#include "core/animation_handler.h"
void LoadMageTextures(void);
void UnloadMageTextures();
AnimationData GetMageAnimationData(int mage_id, int animation_id);
#endif // !MAGE_TEXTURE_H
