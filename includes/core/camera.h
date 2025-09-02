#ifndef CAMERA_H
#define CAMERA_H

#include "player/player.h"
#include "raylib.h"

typedef struct GameCamera {
  Camera2D properties;
  Rectangle view;
  Vector2 *target;
} GameCamera;

void InitCamera(GameCamera *camera, Player *player);
void UpdateCameraOffset(GameCamera *camera);
void UpdateGameCamera(GameCamera *camera);

#endif // CAMERA_H
