#include "core/camera.h"
#include "core/player.h"
#include "core/window.h"
#include "raylib.h"

void InitCamera(Camera2D *camera, Player *player) {
  camera->target = player->position;
  camera->offset =
      (Vector2){GetDisplayWidth() / 2.0f, GetDisplayHeigth() / 2.0f};
  camera->rotation = 0.0f;
  camera->zoom = 1.0f;
}
void UpdateCameraOffset(Camera2D *camera, Player *player) {
  // camera->offset =
  //     (Vector2){GetDisplayWidth() / 2.0f, GetDisplayHeigth() / 2.0f};
  camera->offset = (Vector2){GetRenderWidth() / 2.0f, GetRenderHeight() / 2.0f};
}

void UpdatePlayerCamera(Camera2D *camera, Player *player) {
  camera->target =
      (Vector2){player->position.x + 20.0f, player->position.y + 20.0f};
}
