#ifndef CAMERA_H
#define CAMERA_H

#include "player.h"

void InitCamera(Player *player);
void UpdateCameraOffset(Player *player);
void UpdatePlayerCamera(Player *player);

#endif // CAMERA_H