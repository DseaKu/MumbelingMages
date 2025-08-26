
#include "player.h"
#include <raylib.h>

Player InitPlayer() {
  Player player;

  player.position = (Vector2){400, 225};
  player.size = (Vector2){50, 50};
  player.color = MAROON;
  player.speed = 800.0f;
  player.fireRate = 0.2f;
  player.pickupRange = 50.0f;
  return player;
}

void UpdatePlayer(Player *player, float fireTimer, int screen_width,
                  int screen_height) {
  float delta = GetFrameTime();

  if (IsKeyDown(KEY_W))
    player->position.y -= player->speed * delta;
  if (IsKeyDown(KEY_S))
    player->position.y += player->speed * delta;
  if (IsKeyDown(KEY_A))
    player->position.x -= player->speed * delta;
  if (IsKeyDown(KEY_D))
    player->position.x += player->speed * delta;

  if (player->position.x < 0)
    player->position.x = 0;
  if (player->position.x + player->size.x > screen_width)
    player->position.x = screen_width - player->size.x;
  if (player->position.y < 0)
    player->position.y = 0;
  if (player->position.y + player->size.y > screen_height)
    player->position.y = screen_height - player->size.y;
}

void DrawPlayer(Player player) {
  DrawRectangleV(player.position, player.size, player.color);
}
