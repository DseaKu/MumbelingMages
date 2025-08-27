#ifndef MAP_H
#define MAP_H

typedef struct Map {
  int width;
  int height;
  float map_size_multiplier;
} Map;
void UpdateMap(Map *map);
#endif // !MAP_H
