
#include "player.h"
#include "enemy.h"
#include "map.h"
#include "raymath.h"
#include <raylib.h>
#include <stdbool.h>

Player InitPlayer() {
  Player player;

  player.position = (Vector2){400, 225};
  player.size = (Vector2){120, 135};
  player.color = MAROON;
  player.speed = 500.0f;
  player.fireRate = 0.2f;
  player.pickupRange = 150.0f;
  player.texture = LoadTexture("assets/default_mage2.jpeg");
  player.health = 100;
  return player;
}

void UpdatePlayer(Player *player, float fireTimer, bool is_auto_aim, Map map) {
  float delta = GetFrameTime();

  //------ Movement --------------
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
  if (player->position.x + player->size.x / 2 > map.width)
    player->position.x = map.width - player->size.x / 2;
  if (player->position.y - player->size.y / 2 < 0)
    player->position.y = player->size.y / 2;
  if (player->position.y + player->size.y / 2 > map.height)
    player->position.y = map.height - player->size.y / 2;

  //---- Face direction --------------
  if (!is_auto_aim) {
    if (GetMousePosition().x < player->position.x) {
      player->is_facing_right = false;
    } else {
      player->is_facing_right = true;
    }
  }
  //------- Camera ---------
  player->camera.target =
      (Vector2){player->position.x + 20.0f, player->position.y + 20.0f};
  player->camera.offset = (Vector2){map.width / 2.0f, map.height / 2.0f};
}

void DrawPlayer(Player player) {
  float texture_width = (float)player.texture.width;
  if (!player.is_facing_right) {
    texture_width = -texture_width;
  }

  DrawTexturePro(player.texture,
                 (Rectangle){0, 0, texture_width, (float)player.texture.height},
                 (Rectangle){player.position.x, player.position.y,
                             player.size.x, player.size.y},
                 (Vector2){player.size.x / 2, player.size.y / 2}, 0, WHITE);
}
bool IsPlayerHit(Player player, Enemy *enemies, bool *game_over) {

  // Check if player is hitted
  for (int i = 0; i < MAX_ENEMIES; i++) {
    if (enemies[i].active &&
        CheckCollisionRecs((Rectangle){player.position.x - player.size.x / 2,
                                       player.position.y - player.size.y / 2,
                                       player.size.x, player.size.y},
                           (Rectangle){enemies[i].position.x,
                                       enemies[i].position.y, enemies[i].size.x,
                                       enemies[i].size.y})) {
      *game_over = true;
    }
  }
  return true;
}
