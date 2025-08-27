#include "map.h"
#include "window.h"
#include <stdlib.h>
#include <time.h>

void InitMap(Map *map) {

  map->map_multiplier = 2.0f;
  map->width = GetDisplayWidth() * map->map_multiplier;
  map->height = map->width * XY_RATIO;
}
