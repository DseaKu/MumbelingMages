#include "mage_properties.h"
#include "player.h"
#include "sprite.h"
#include <raylib.h>
static Player mage_properties[SIZE_SPRITE_ID];

void LoadMageProperties() {
  mage_properties[MAGE] = (Player){
      .state = WALKING,
      .id = MAGE,
      .position = (Vector2){400, 225},
      .hit_box = (Vector2){120, 160},
      .speed = 500.0f,
      .fireRate = 0.2f,
      .pickupRange = 150.0f,
      .health = 100,
  };
};
Player GetMageProperties(int mage_id) { return mage_properties[mage_id]; }
