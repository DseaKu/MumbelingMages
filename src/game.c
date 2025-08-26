#include "game.h"
#include "bullet.h"
#include "enemy.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void GameLoop() {

  //----------------------------------------------------------------------------------
  // INIT
  //----------------------------------------------------------------------------------
  const int screen_width = 1300;
  const int screen_height = 900;

  InitWindow(screen_width, screen_height, "Mumbeling Mages");

  Player player = InitPlayer();
  Bullet bullets[MAX_BULLETS];
  Enemy enemies[MAX_ENEMIES];
  PowerUp powerUps[MAX_POWERUPS];
  int score;
  bool gameOver;

  srand(time(NULL));

  InitGame(bullets, enemies, powerUps, &score, &gameOver);

  float fireTimer = 0.0f;
  float enemySpawnTimer = 0.0f;
  float powerUpSpawnTimer = 0.0f;

  // SetTargetFPS(60);

  do {

    //----------------------------------------------------------------------------------
    // Update
    //----------------------------------------------------------------------------------
    fireTimer += GetFrameTime();
    enemySpawnTimer += GetFrameTime();
    powerUpSpawnTimer += GetFrameTime();
    UpdatePlayer(&player, fireTimer, screen_width, screen_height);

    FireBullet(bullets, player.position, fireTimer, player.fireRate);
    if (fireTimer >= player.fireRate && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
      fireTimer = 0;
    }

    if (enemySpawnTimer >= 1.0f) {
      SpawnEnemy(enemies, screen_width, screen_height);
      enemySpawnTimer = 0.0f;
    }
    if (powerUpSpawnTimer >= 10.0f) {
      SpawnPowerUp(powerUps);
      powerUpSpawnTimer = 0.0f;
    }
    UpdateEnemies(enemies, player.position);
    UpdatePowerUps(powerUps, &player);
    UpdateBullets(bullets, screen_width, screen_height);
    CheckBulletCollision(bullets, enemies, &score);

    // Check if player is hitted
    for (int i = 0; i < MAX_ENEMIES; i++) {
      if (enemies[i].active &&
          CheckCollisionRecs(
              (Rectangle){player.position.x, player.position.y, player.size.x,
                          player.size.y},
              (Rectangle){enemies[i].position.x, enemies[i].position.y,
                          enemies[i].size.x, enemies[i].size.y})) {
        gameOver = true;
      }
    }

    //----------------------------------------------------------------------------------
    // Draw
    //----------------------------------------------------------------------------------
    DrawGame(player, bullets, enemies, powerUps, score, gameOver, screen_width,
             screen_height);

  } while (!WindowShouldClose());

  CloseWindow();
}
void InitGame(Bullet *bullets, Enemy *enemies, PowerUp *powerUps, int *score,
              bool *gameOver) {
  InitBullets(bullets);
  InitEnemies(enemies);
  InitPowerUps(powerUps);
  *score = 0;
  *gameOver = false;
}

void CheckBulletCollision(Bullet *bullets, Enemy *enemies, int *score) {

  for (int i = 0; i < MAX_BULLETS; i++) {
    if (bullets[i].active) {
      for (int j = 0; j < MAX_ENEMIES; j++) {
        if (enemies[j].active &&
            CheckCollisionRecs(
                (Rectangle){bullets[i].position.x, bullets[i].position.y,
                            bullets[i].size.x, bullets[i].size.y},
                (Rectangle){enemies[j].position.x, enemies[j].position.y,
                            enemies[j].size.x, enemies[j].size.y})) {
          bullets[i].active = false;
          enemies[j].active = false;
          *score += 10;
        }
      }
    }
  }
}

void DrawGame(Player player, Bullet *bullets, Enemy *enemies, PowerUp *powerUps,
              int score, bool gameOver, int screen_width, int screen_height) {
  BeginDrawing();
  ClearBackground(RAYWHITE);

  if (!gameOver) {
    DrawPlayer(player);
    DrawEnemies(enemies);
    DrawBullets(bullets);
    DrawPowerUps(powerUps);
    DrawFPS(screen_width - 100, 10);

    char scoreText[20];
    sprintf(scoreText, "Score: %d", score);
    DrawText(scoreText, 10, 10, 20, LIGHTGRAY);
  } else {
    DrawText("GAME OVER", screen_width / 2 - MeasureText("GAME OVER", 40) / 2,
             screen_height / 2 - 20, 40, RED);
    DrawText("Press 'R' to restart",
             screen_width / 2 - MeasureText("Press 'R' to restart", 20) / 2,
             screen_height / 2 + 20, 20, GRAY);
  }

  EndDrawing();
}
