#include "map.h"
#include "math.h"
#include "window.h"

void UpdateMap(Map *map) {

  map->width = floorf(GetDisplayWidth() * map->map_size_multiplier);
  map->height = floorf(GetDisplayHeigth() * map->map_size_multiplier);
}
