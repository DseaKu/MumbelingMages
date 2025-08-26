
#include "player.h"
#include <raylib.h>

Player InitPlayer() {
  Player player;

  player.position = (Vector2){400, 225};
  player.size = (Vector2){50, 50};
  player.color = MAROON;
  player.speed = 800.0f;
  player.fireRate = 0.2f;
  return player;
}

void UpdatePlayer(Player *player, float fireTimer) {
  float delta = GetFrameTime();

  if (IsKeyDown(KEY_W))
    player->position.y -= player->speed * delta;
  if (IsKeyDown(KEY_S))
    player->position.y += player->speed * delta;
  if (IsKeyDown(KEY_A))
    player->position.x -= player->speed * delta;
  if (IsKeyDown(KEY_D))
    player->position.x += player->speed * delta;
}

void DrawPlayer(Player player) {
  DrawRectangleV(player.position, player.size, player.color);
}
