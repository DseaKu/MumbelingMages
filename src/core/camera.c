#include "core/camera.h"
#include "core/window.h"
#include "raylib.h"

void InitCamera(GameCamera *camera, Player *player) {

  camera->target = &player->position;
  camera->properties.target = player->position;
  camera->properties.offset =
      (Vector2){GetDisplayWidth() / 2.0f, GetDisplayHeigth() / 2.0f};
  camera->properties.rotation = 0.0f;
  camera->properties.zoom = 1.0f;
}
void UpdateCameraOffset(GameCamera *camera) {
  camera->properties.offset =
      (Vector2){GetRenderWidth() / 2.0f, GetRenderHeight() / 2.0f};
}

void UpdateGameCamera(GameCamera *camera) {
  camera->properties.target =
      (Vector2){camera->target->x + 20.0f, camera->target->y + 20.0f};

  // Update Camera view
  u32 screen_width = GetDisplayWidth();
  u32 screen_heigth = GetRenderHeight();

  Vector2 camera_top_left = {
      camera->properties.target.x -
          (screen_width / 2.0f) / camera->properties.zoom,
      camera->properties.target.y -
          (screen_heigth / 2.0f) / camera->properties.zoom};

  camera->view = (Rectangle){camera_top_left.x, camera_top_left.y,
                             screen_width / camera->properties.zoom,
                             screen_heigth / camera->properties.zoom};
}
