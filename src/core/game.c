#include "core/game.h"
#include "core/IO_handler.h"
#include "core/bullet.h"
#include "core/camera.h"
#include "core/map.h"
#include "core/orb.h"
#include "core/resource_tracker.h"
#include "core/window.h"
#include "enemy/enemy.h"
#include "enemy/enemy_properties.h"
#include "enemy/enemy_texture.h"
#include "mumble/mumble.h"
#include "player/player.h"
#include "player/player_properties.h"
#include "player/player_texture.h"
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
  StartPerformanceTracker("Init");
  // SetConfigFlags(FLAG_WINDOW_HIGHDPI);
  int screen_width = GetDisplayWidth();
  int screen_height = GetDisplayHeigth();

  InitWindow(screen_width, screen_height, "Mumbeling Mages");

  Player player;
  Bullet bullets[MAX_BULLETS] = {0};
  MumbleData mumble_data = {0};
  EnemyData enemy_data = {0};
  PowerUp powerUps[MAX_POWERUPS];
  IO_Flags io_flags = 0;
  GameCamera camera;
  bool is_game_over = false;
  srand(time(NULL));

  InitGame(bullets, &enemy_data, powerUps, &exp, &map, &io_flags, &player,
           &camera);

  float fireTimer = 0.0f;
  float enemySpawnTimer = 0.0f;
  float powerUpSpawnTimer = 0.0f;

  // SetTargetFPS(60);

  EndPerformanceTracker("Init");
  //----------------------------------------------------------------------------------
  // Game loop
  //----------------------------------------------------------------------------------
  do {
    StartPerformanceTracker("CompleteLoop");
    //----------------------------------------------------------------------------------
    // Check inputs
    //----------------------------------------------------------------------------------
    StartPerformanceTracker("Get Inputs");
    GetInputs(&io_flags);
    EndPerformanceTracker("Get Inputs");

    //----------------------------------------------------------------------------------
    // Spawning
    //----------------------------------------------------------------------------------
    StartPerformanceTracker("Spawning");
    if (fireTimer >= player.fireRate &&
        (io_flags & IS_MOUSE_LEFT_PRESSED || io_flags & AUTO_AIM)) {
      FireBullet(bullets, &player, player.fireRate, io_flags & AUTO_AIM,
                 &enemy_data, camera);
      fireTimer = 0;
    }

    if (io_flags & CAST_MUMBLE) {
      CastFireball(&mumble_data);
    }

    if (enemySpawnTimer >= 1.0f) {
      SpawnEnemy(&enemy_data, map, player.position);
      enemySpawnTimer = 0.0f;
    }
    if (powerUpSpawnTimer >= 10.0f) {
      SpawnPowerUp(powerUps);
      powerUpSpawnTimer = 0.0f;
    }
    EndPerformanceTracker("Spawning");

    //----------------------------------------------------------------------------------
    // Update
    //----------------------------------------------------------------------------------
    StartPerformanceTracker("Update");
    if (io_flags & TOGGLE_FULLSCREEN) {
      ToggleRealFullscreen();
      UpdateCameraOffset(&camera);

      io_flags -= TOGGLE_FULLSCREEN;
    }
    if (io_flags & AUTO_AIM) {
      HideCursor();
    } else {
      ShowCursor();
    }
    if (!(io_flags & PAUSE_GAME)) {
      fireTimer += GetFrameTime();
      enemySpawnTimer += GetFrameTime();
      powerUpSpawnTimer += GetFrameTime();
      UpdatePlayer(&player, fireTimer, io_flags & AUTO_AIM, map);
      UpdateEnemies(&enemy_data, player.position, map);
      UpdateMumbles(&mumble_data, &player, &enemy_data);
      UpdatePowerUps(powerUps, &player);
      UpdateBullets(bullets, map);
      UpdateOrbs();
      UpdateGameCamera(&camera);
    }
    EndPerformanceTracker("Update");

    //----------------------------------------------------------------------------------
    // Collision
    //----------------------------------------------------------------------------------
    StartPerformanceTracker("Collision");
    CheckBulletCollision(bullets, &enemy_data);
    // CheckBulletColision(bullets, &enemy_data);
    CheckOrbPickup(&player, &exp);
    if (!is_game_over) {
      CheckPlayerCollision(&player, &enemy_data);
      if (player.health <= 0) {
        is_game_over = true;
      }
    }
    EndPerformanceTracker("Collision");
    //----------------------------------------------------------------------------------
    // Draw
    //----------------------------------------------------------------------------------
    StartPerformanceTracker("Drawing");
    BeginDrawing();
    ClearBackground(RAYWHITE);

    if (!is_game_over) {
      BeginMode2D(camera.properties);
      DrawMap(map);
      DrawBullets(bullets);
      DrawPlayer(&player, io_flags & PAUSE_GAME, camera.view);
      DrawPowerUps(powerUps);
      DrawOrbs();
      DrawEnemies(&enemy_data, io_flags & PAUSE_GAME, camera.view);

      EndMode2D();

      // Draw UI
      DrawFPS(GetDisplayWidth() - 100, 10);
      char healthText[20];
      sprintf(healthText, "Health: %d", player.health);
      DrawText(healthText, 20, 20, 20, GREEN);

      DrawDebugText();

      if (io_flags & AUTO_AIM) {
        DrawText("Auto Aim", 20, 60, 20, GREEN);
      } else {
        DrawText("Auto Aim", 20, 60, 20, MAROON);
      }
      if (io_flags & PAUSE_GAME) {
        DrawText("PAUSED",
                 GetDisplayWidth() / 2 - MeasureText("PAUSED", 40) / 2,
                 GetDisplayHeigth() / 2 - 20, 40, RED);
      }
      if (PIXELFORMAT_UNCOMPRESSED_R5G5B5A1) {
      }
      char expText[20];
      sprintf(expText, "EXP: %d", exp);
      DrawText(expText, GetDisplayWidth() / 2 - MeasureText("EXP:", 20), 10, 20,
               LIGHTGRAY);
    } else {
      DrawText("Nice try, noob!",
               GetDisplayWidth() / 2 - MeasureText("Nice try, noob!", 40) / 2,
               GetDisplayHeigth() / 2 - 20, 40, RED);
    }
    EndPerformanceTracker("Drawing");

    StartPerformanceTracker("End Drawing");
    EndDrawing();
    EndPerformanceTracker("End Drawing");

    EndPerformanceTracker("CompleteLoop");
  } while (!WindowShouldClose());

  UnloadGame(player, map);
  CloseWindow();
  PrintPerformanceTrackers();
}

void InitGame(Bullet *bullets, EnemyData *enemy_data, PowerUp *powerUps,
              int *exp, Map *map, IO_Flags *io_flags, Player *player,
              GameCamera *camera) {
  LoadMageTextures();
  LoadEnemyTextures();
  LoadEnemyProperties();
  LoadMageProperties();
  InitIO_Flags(io_flags);
  InitBullets(bullets);
  InitEnemies(enemy_data);
  InitPowerUps(powerUps);
  InitOrbs();
  InitMap(map);
  InitPlayer(player);
  InitCamera(camera, player);
  *exp = 0;
}
void UnloadGame(Player player, Map map) {
  UnloadMageTextures();
  UnloadEnemyTextures();
  UnloadMap(map);
}
