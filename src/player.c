
#include "player.h"
#include "raymath.h"
#include <raylib.h>

Player InitPlayer() {
  Player player;

  player.position = (Vector2){400, 225};
  player.size = (Vector2){120, 135};
  player.color = MAROON;
  player.speed = 500.0f;
  player.fireRate = 0.2f;
  player.pickupRange = 150.0f;
  player.texture = LoadTexture("assets/default_mage2.jpeg");
  return player;
}

void UpdatePlayer(Player *player, float fireTimer, int screen_width,
                  int screen_height) {
  float delta = GetFrameTime();
  Vector2 direction = {0, 0};

  if (IsKeyDown(KEY_W))
    direction.y = -1;
  if (IsKeyDown(KEY_S))
    direction.y = 1;
  if (IsKeyDown(KEY_A))
    direction.x = -1;
  if (IsKeyDown(KEY_D))
    direction.x = 1;

  if (Vector2Length(direction) > 0) {
    direction = Vector2Normalize(direction);
  }

  player->position.x += direction.x * player->speed * delta;
  player->position.y += direction.y * player->speed * delta;

  if (player->position.x - player->size.x / 2 < 0)
    player->position.x = player->size.x / 2;
  if (player->position.x + player->size.x / 2 > screen_width)
    player->position.x = screen_width - player->size.x / 2;
  if (player->position.y - player->size.y / 2 < 0)
    player->position.y = player->size.y / 2;
  if (player->position.y + player->size.y / 2 > screen_height)
    player->position.y = screen_height - player->size.y / 2;
}

void DrawPlayer(Player player) {
  float texture_width = (float)player.texture.width;
  if (GetMousePosition().x < player.position.x) {
    texture_width = -texture_width;
  }
  DrawTexturePro(player.texture,
                 (Rectangle){0, 0, texture_width, (float)player.texture.height},
                 (Rectangle){player.position.x, player.position.y,
                             player.size.x, player.size.y},
                 (Vector2){player.size.x / 2, player.size.y / 2}, 0, WHITE);
}
