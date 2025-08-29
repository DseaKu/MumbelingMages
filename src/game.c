#include "game.h"
#include "IO_handler.h"
#include "animation_handler.h"
#include "bullet.h"
#include "enemy.h"
#include "map.h"
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
  // Declaration
  //----------------------------------------------------------------------------------
  Map map;
  int exp;

  //----------------------------------------------------------------------------------
  // INIT
  //----------------------------------------------------------------------------------
  int screen_width = GetDisplayWidth();
  int screen_height = GetDisplayHeigth();

  InitWindow(screen_width, screen_height, "Mumbeling Mages");

  Player player = InitPlayer(screen_width, screen_height);
  Bullet bullets[MAX_BULLETS] = {0};
  Enemy enemies[MAX_ENEMIES] = {0};
  PowerUp powerUps[MAX_POWERUPS];
  Orb orbs[MAX_ORBS];
  IO_Flags io_flags = 0;
  bool is_game_over = false;

  srand(time(NULL));

  InitGame(bullets, enemies, powerUps, orbs, &exp, &map, &io_flags);

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
    GetInputs(&io_flags);

    //----------------------------------------------------------------------------------
    // Spawning
    //----------------------------------------------------------------------------------
    if (fireTimer >= player.fireRate &&
        ((IsMouseButtonDown(MOUSE_LEFT_BUTTON)) || io_flags & AUTO_AIM)) {
      FireBullet(bullets, &player, player.fireRate, io_flags & AUTO_AIM,
                 enemies);
      fireTimer = 0;
    }

    if (enemySpawnTimer >= 1.0f) {
      SpawnEnemy(enemies, map, player.position);
      enemySpawnTimer = 0.0f;
    }
    if (powerUpSpawnTimer >= 10.0f) {
      SpawnPowerUp(powerUps);
      powerUpSpawnTimer = 0.0f;
    }

    //----------------------------------------------------------------------------------
    // Update
    //----------------------------------------------------------------------------------
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
      UpdateEnemies(enemies, player.position);
      UpdatePowerUps(powerUps, &player);
      UpdateBullets(bullets, map);
      UpdateOrbs(orbs);
    }

    //----------------------------------------------------------------------------------
    // Collision
    //----------------------------------------------------------------------------------
    CheckBulletCollision(bullets, enemies, orbs);
    CheckOrbPickup(&player, orbs, &exp);
    if (!is_game_over) {
      CheckPlayerCollision(&player, enemies);
      if (player.health <= 0) {
        is_game_over = true;
      }
    }

    //----------------------------------------------------------------------------------
    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();
    ClearBackground(RAYWHITE);

    if (!is_game_over) {
      BeginMode2D(player.camera);
      DrawMap(map);
      DrawBullets(bullets);
      DrawPlayer(player);
      DrawPowerUps(powerUps);
      DrawOrbs(orbs);
      DrawEnemies(enemies);
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
    EndDrawing();

  } while (!WindowShouldClose());

  UnloadGame(player, map);
  CloseWindow();
}

void InitGame(Bullet *bullets, Enemy *enemies, PowerUp *powerUps, Orb *orbs,
              int *exp, Map *map, IO_Flags *io_flags) {
  InitIO_Flags(io_flags);
  InitBullets(bullets);
  InitEnemies(enemies);
  InitPowerUps(powerUps);
  InitOrbs(orbs);
  *exp = 0;
  InitMap(map);
  LoadTextures();
}
void UnloadGame(Player player, Map map) {
  UnloadTexture(player.texture);
  UnloadTextures();
  UnloadMap(map);
}
