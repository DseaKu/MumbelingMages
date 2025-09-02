#include "player/player_properties.h"
#include "player/player.h"
#include "player/player_sprite.h"
#include "player/player_texture.h"
#include <raylib.h>
static Player mage_properties[SIZE_PLAYER_SPRITE_ID];

void LoadMageProperties() {
  mage_properties[MAGE] = (Player){
      .state = MAGE_WALKING,
      .id = MAGE,
      .position = (Vector2){400, 225},
      .hit_box = (Vector2){120, 160},
      .speed = 500.0f,
      .fireRate = 0.2f,
      .pickupRange = 150.0f,
      .health = 100,
      .get_animation_data = GetMageAnimationData,
  };
};
Player GetMageProperties(int mage_id) { return mage_properties[mage_id]; }
