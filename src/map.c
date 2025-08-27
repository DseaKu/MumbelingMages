#include "map.h"
#include "window.h"
#include <raylib.h>
#include <stdlib.h>
#include <time.h>

void InitMap(Map *map) {

  map->map_multiplier = 2.0f;
  map->width = GetDisplayWidth() * map->map_multiplier;
  map->height = map->width * XY_RATIO;
  Image image = LoadImage("assets/Map.png");
  map->texture = LoadTextureFromImage(image);
  UnloadImage(image);
}

void DrawMap(Map map) {
  DrawTexturePro(map.texture,
                 (Rectangle){0, 0, (float)map.texture.width,
                             (float)map.texture.height},
                 (Rectangle){0, 0, (float)map.width, (float)map.height},
                 (Vector2){0, 0}, 0, WHITE);
}

void UnloadMap(Map map) { UnloadTexture(map.texture); }
