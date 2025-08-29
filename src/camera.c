#include "camera.h"
#include "player.h"
#include "window.h"

void InitCamera(Player *player) {
    player->camera.target = player->position;
    player->camera.offset = (Vector2){GetDisplayWidth() / 2.0f, GetDisplayHeigth() / 2.0f};
    player->camera.rotation = 0.0f;
    player->camera.zoom = 1.0f;
}

void UpdatePlayerCamera(Player *player) {
    player->camera.target = (Vector2){player->position.x + 20.0f, player->position.y + 20.0f};
}
