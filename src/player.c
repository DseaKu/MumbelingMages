
#include "player.h"
#include "animation_handler.h"
#include "enemy.h"
#include "map.h"
#include "raymath.h"
#include "sprite.h"
#include "window.h"
#include <raylib.h>
#include <stdbool.h>

Player InitPlayer(int screen_width, int screen_height) {
  Player player;
  player.state = WALKING;
  player.id = MAGE;
  player.position = (Vector2){400, 225};
  player.hit_box = (Vector2){120, 160};
  player.speed = 500.0f;
  player.fireRate = 0.2f;
  player.pickupRange = 150.0f;
  player.health = 100;
  player.camera.target = player.position;
  player.camera.offset =
      (Vector2){GetDisplayWidth() / 2.0f, GetDisplayHeigth() / 2.0f};
  player.camera.rotation = 0.0f;
  player.camera.zoom = 1.0f;
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

  if (player->position.x - player->hit_box.x / 2 < 0)
    player->position.x = player->hit_box.x / 2;
  if (player->position.x + player->hit_box.x / 2 > map.width)
    player->position.x = map.width - player->hit_box.x / 2;
  if (player->position.y - player->hit_box.y / 2 < 0)
    player->position.y = player->hit_box.y / 2;
  if (player->position.y + player->hit_box.y / 2 > map.height)
    player->position.y = map.height - player->hit_box.y / 2;

  //---- Face direction --------------
  if (!is_auto_aim) {
    if (GetMousePosition().x < player->position.x) {
      player->animation.is_facing_right = false;
    } else {
      player->animation.is_facing_right = true;
    }
  }
  //------- Camera ---------
  player->camera.target =
      (Vector2){player->position.x + 20.0f, player->position.y + 20.0f};
  player->camera.offset =
      (Vector2){GetDisplayWidth() / 2.0f, GetDisplayHeigth() / 2.0f};
}

void DrawPlayer(Player *player, bool is_pause) {
  PlayAnimation(player->hit_box, player->position, &player->animation,
                player->id, player->state, is_pause);
}

void CheckPlayerCollision(Player *player, EnemyData *enemy_data) {
  Enemy *enemies = enemy_data->enemies;

  // Check if player is hitted
  for (int i = 0; i < MAX_ENEMIES; i++) {
    if (enemy_data->state[i] != INACTIVE &&
        CheckCollisionRecs(
            (Rectangle){player->position.x - player->hit_box.x / 2,
                        player->position.y - player->hit_box.y / 2,
                        player->hit_box.x, player->hit_box.y},
            (Rectangle){enemies[i].position.x, enemies[i].position.y,
                        enemies[i].hit_box.x, enemies[i].hit_box.y})) {
      if (enemies[i].hit_cooldown <= 0) {
        player->health -= enemies[i].damage;
        enemies[i].hit_cooldown = enemies[i].attack_speed;

        // Push enemy back slightly to prevent continuous damage
        Vector2 push_direction = Vector2Normalize(
            Vector2Subtract(enemies[i].position, player->position));
        enemies[i].position = Vector2Add(enemies[i].position,
                                         Vector2Scale(push_direction, 100.0f));
      }
    }
  }
}
