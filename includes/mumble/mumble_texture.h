#ifndef MUMBLE_TEXTURE_H
#define MUMBLE_TEXTURE_H
#include "core/animation_handler.h"

void LoadMumbleTextures(void);
void UnloadMumbleTextures(void);
AnimationData GetMumbleAnimationData(int sprite_id, int mumble_id);
#endif // !MUMBLE_TEXTURE_H
