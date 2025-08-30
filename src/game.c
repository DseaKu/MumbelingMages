#include "game.h"
#include "IO_handler.h"
#include "animation_handler.h"
#include "bullet.h"
#include "camera.h"
#include "enemy.h"
#include "enemy_properties.h"
#include "mage_properties.h"
#include "map.h"
#include "orb.h"
#include "player.h"
#include "resource_tracker.h"
#include "window.h"
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
  int screen_width = GetDisplayWidth();
  int screen_height = GetDisplayHeigth();

  InitWindow(screen_width, screen_height, "Mumbeling Mages");

  Player player;
  Bullet bullets[MAX_BULLETS] = {0};
  EnemyData enemy_data = {0};
  PowerUp powerUps[MAX_POWERUPS];
  Orb orbs[MAX_ORBS];
  IO_Flags io_flags = 0;
  bool is_game_over = false;

  srand(time(NULL));

  InitGame(bullets, &enemy_data, powerUps, orbs, &exp, &map, &io_flags,
           &player);

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
        ((IsMouseButtonDown(MOUSE_LEFT_BUTTON)) || io_flags & AUTO_AIM)) {
      FireBullet(bullets, &player, player.fireRate, io_flags & AUTO_AIM,
                 &enemy_data);
      fireTimer = 0;
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
      ToggleRealFullscreen(screen_width, screen_height);
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
      UpdatePowerUps(powerUps, &player);
      UpdateBullets(bullets, map);
      UpdateOrbs(orbs);
      UpdatePlayerCamera(&player);
    }
    EndPerformanceTracker("Update");

    //----------------------------------------------------------------------------------
    // Collision
    //----------------------------------------------------------------------------------
    StartPerformanceTracker("Collision");
    CheckBulletCollision(bullets, &enemy_data, orbs);
    CheckOrbPickup(&player, orbs, &exp);
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
      BeginMode2D(player.camera);
      DrawMap(map);
      DrawBullets(bullets);
      DrawPlayer(&player, io_flags & PAUSE_GAME);
      DrawPowerUps(powerUps);
      DrawOrbs(orbs);
      DrawEnemies(&enemy_data, io_flags & PAUSE_GAME);
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
              Orb *orbs, int *exp, Map *map, IO_Flags *io_flags,
              Player *player) {
  LoadTextures();
  LoadEnemyProperties();
  LoadMageProperties();
  InitIO_Flags(io_flags);
  InitBullets(bullets);
  InitEnemies(enemy_data);
  InitPowerUps(powerUps);
  InitOrbs(orbs);
  InitMap(map);
  InitPlayer(player);
  InitCamera(player);
  *exp = 0;
}
void UnloadGame(Player player, Map map) {
  UnloadTextures();
  UnloadMap(map);
}
