#include "game.h"
#include "bullet.h"
#include "enemy.h"
#include "map.h"
#include "orb.h"
#include "player.h"
#include "window.h"
#include <math.h>
#include <raylib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void GameLoop() {
  //----------------------------------------------------------------------------------
  // Declaration
  //----------------------------------------------------------------------------------
  Map map;
  int exp;

  //----------------------------------------------------------------------------------
  // INIT
  //----------------------------------------------------------------------------------
  int screen_width = 1300;
  int screen_height = 800;

  InitWindow(screen_width, screen_height, "Mumbeling Mages");

  Player player = InitPlayer();
  Bullet bullets[MAX_BULLETS] = {0};
  Enemy enemies[MAX_ENEMIES] = {0};
  PowerUp powerUps[MAX_POWERUPS];
  Orb orbs[MAX_ORBS];
  bool is_game_over = false;
  bool is_pause_game = false;
  bool is_auto_aim = true;

  Camera2D camera = {0};
  camera.offset = (Vector2){screen_width / 2.0f, screen_height / 2.0f};
  camera.rotation = 0.0f;
  camera.zoom = 1.0f;

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
      is_auto_aim = !is_auto_aim;
    }
    //----------------------------------------------------------------------------------
    // Spawning
    //----------------------------------------------------------------------------------
    if (fireTimer >= player.fireRate &&
        ((IsMouseButtonDown(MOUSE_LEFT_BUTTON)) || is_auto_aim)) {
      FireBullet(bullets, &player, player.fireRate, is_auto_aim, enemies);
      fireTimer = 0;
    }

    if (enemySpawnTimer >= 1.0f) {
      SpawnEnemy(enemies, map);
      enemySpawnTimer = 0.0f;
    }
    if (powerUpSpawnTimer >= 10.0f) {
      SpawnPowerUp(powerUps);
      powerUpSpawnTimer = 0.0f;
    }

    //----------------------------------------------------------------------------------
    // Update
    //----------------------------------------------------------------------------------
    if (is_auto_aim) {
      HideCursor();
    } else {
      ShowCursor();
    }
    if (!is_pause_game) {
      fireTimer += GetFrameTime();
      enemySpawnTimer += GetFrameTime();
      powerUpSpawnTimer += GetFrameTime();
      UpdatePlayer(&player, fireTimer, is_auto_aim, map);
      UpdateEnemies(enemies, player.position);
      UpdatePowerUps(powerUps, &player);
      UpdateBullets(bullets, map);
      UpdateOrbs(orbs);
    }

    camera.target = player.position;

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
      BeginMode2D(camera);
      DrawBullets(bullets);
      DrawPlayer(player);
      DrawPowerUps(powerUps);
      DrawOrbs(orbs);
      DrawEnemies(enemies);
      EndMode2D();
      DrawFPS(GetDisplayWidth() - 100, 10);
      if (is_auto_aim) {
        DrawText("Auto Aim", 20, 60, 20, GREEN);
      } else {
        DrawText("Auto Aim", 20, 60, 20, MAROON);
      }
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
  map->width = floorf(GetDisplayWidth() * map->map_size_multiplier);
  map->height = floorf(GetDisplayHeigth() * map->map_size_multiplier);
}
void UnloadGame(Player player) { UnloadTexture(player.texture); }
