#include "game.h"
#include "bullet.h"
#include "enemy.h"
#include "orb.h"
#include "player.h"
#include "window.h"
#include <raylib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void GameLoop() {

  //----------------------------------------------------------------------------------
  // INIT
  //----------------------------------------------------------------------------------
  int screen_width = 1300;
  int screen_height = 800;

  InitWindow(screen_width, screen_height, "Mumbeling Mages");

  Player player = InitPlayer();
  Bullet bullets[MAX_BULLETS];
  Enemy enemies[MAX_ENEMIES];
  PowerUp powerUps[MAX_POWERUPS];
  Orb orbs[MAX_ORBS];
  Map map;
  int exp;
  bool is_game_over = false;
  bool is_pause_game = false;
  bool isauto_aim = true;

  srand(time(NULL));

  InitGame(bullets, enemies, powerUps, orbs, &exp, &map);

  float fireTimer = 0.0f;
  float enemySpawnTimer = 0.0f;
  float powerUpSpawnTimer = 0.0f;

  // SetTargetFPS(60);

  //----------------------------------------------------------------------------------
  // Game loop
  //----------------------------------------------------------------------------------

  do {
    //----------------------------------------------------------------------------------
    // Check inputs
    //----------------------------------------------------------------------------------
    if (IsKeyPressed(KEY_F)) {
      is_pause_game = !is_pause_game;
    }
    if (IsKeyPressed(KEY_T)) {
      ToggleRealFullscreen(screen_width, screen_height);
    }
    if (IsKeyPressed(KEY_E)) {
      isauto_aim = !isauto_aim;
    }
    //----------------------------------------------------------------------------------
    // Sawning
    //----------------------------------------------------------------------------------
    FireBullet(bullets, player.position, fireTimer, player.fireRate,
               isauto_aim);
    if (fireTimer >= player.fireRate && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
      fireTimer = 0;
    }

    if (enemySpawnTimer >= 1.0f) {
      SpawnEnemy(enemies);
      enemySpawnTimer = 0.0f;
    }
    if (powerUpSpawnTimer >= 10.0f) {
      SpawnPowerUp(powerUps);
      powerUpSpawnTimer = 0.0f;
    }

    //----------------------------------------------------------------------------------
    // Update
    //----------------------------------------------------------------------------------
    if (!is_pause_game) {
      fireTimer += GetFrameTime();
      enemySpawnTimer += GetFrameTime();
      powerUpSpawnTimer += GetFrameTime();
      UpdatePlayer(&player, fireTimer);
      UpdateEnemies(enemies, player.position);
      UpdatePowerUps(powerUps, &player);
      UpdateBullets(bullets);
      UpdateOrbs(orbs);
    }

    //----------------------------------------------------------------------------------
    // Collision
    //----------------------------------------------------------------------------------
    CheckBulletCollision(bullets, enemies, orbs);
    CheckOrbPickup(&player, orbs, &exp);
    IsPlayerHit(player, enemies, &is_game_over);

    //----------------------------------------------------------------------------------
    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();
    ClearBackground(RAYWHITE);

    if (!is_game_over) {
      DrawPlayer(player);
      DrawBullets(bullets);
      DrawPowerUps(powerUps);
      DrawOrbs(orbs);
      DrawEnemies(enemies);
      DrawFPS(GetDisplayWidth() - 100, 10);
      if (is_pause_game) {

        DrawText("PAUSED",
                 GetDisplayWidth() / 2 - MeasureText("PAUSED", 40) / 2,
                 GetDisplayHeigth() / 2 - 20, 40, RED);
      }
      if (PIXELFORMAT_UNCOMPRESSED_R5G5B5A1) {
      }
      char expText[20];
      sprintf(expText, "EXP: %d", exp);
      DrawText(expText, 10, 10, 20, LIGHTGRAY);
    } else {
      DrawText("Nice try, noob!",
               GetDisplayWidth() / 2 - MeasureText("Nice try, noob!", 40) / 2,
               GetDisplayHeigth() / 2 - 20, 40, RED);
    }
    EndDrawing();

  } while (!WindowShouldClose());

  UnloadGame(player);
  CloseWindow();
}

void InitGame(Bullet *bullets, Enemy *enemies, PowerUp *powerUps, Orb *orbs,
              int *exp, Map *map) {
  InitBullets(bullets);
  InitEnemies(enemies);
  InitPowerUps(powerUps);
  InitOrbs(orbs);
  *exp = 0;
  map->map_size_multiplier = 1.5;
  map->width = GetDisplayWidth() * map->map_size_multiplier;
  map->height = GetDisplayHeigth() * map->map_size_multiplier;
}
void UnloadGame(Player player) { UnloadTexture(player.texture); }
