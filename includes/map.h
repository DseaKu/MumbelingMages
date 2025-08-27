#ifndef MAP_H

#define MAP_H
#define XY_RATIO 0.75f
#include <raylib.h>

typedef struct Map {
  Texture2D texture;
  int width;
  int height;
  float map_multiplier;
} Map;

void InitMap(Map *map);
#endif // !MAP_H
