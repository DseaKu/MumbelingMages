#ifndef CAMERA_H
#define CAMERA_H

#include "player/player.h"

void InitCamera(Camera2D *camera, Player *player);
void UpdateCameraOffset(Camera2D *camera, Player *player);
void UpdatePlayerCamera(Camera2D *camera, Player *player);

#endif // CAMERA_H
