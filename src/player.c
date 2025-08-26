
#include "player.h"

void InitPlayer(Player *player)
{
    player->position = (Vector2){ 400, 225 };
    player->size = (Vector2){ 50, 50 };
    player->color = MAROON;
    player->speed = 5.0f;
    player->fireRate = 0.2f;
}

void UpdatePlayer(Player *player, float fireTimer)
{
    if (IsKeyDown(KEY_W)) player->position.y -= player->speed;
    if (IsKeyDown(KEY_S)) player->position.y += player->speed;
    if (IsKeyDown(KEY_A)) player->position.x -= player->speed;
    if (IsKeyDown(KEY_D)) player->position.x += player->speed;
}

void DrawPlayer(Player player)
{
    DrawRectangleV(player.position, player.size, player.color);
}
