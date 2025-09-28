#include "mumble/mumble_properties.h"
#include "mumble/mumble.h"
#include "mumble/mumble_sprite.h"
static Mumble mumble_properties[SIZE_MUMBLE_SPRITE_ID];

void LoadMumbleProperties() {
  mumble_properties[FIREBALL] = (Mumble){
      .id = FIREBALL,
      .damage = 200u,
      .speed = (Vector2){350.0f, 350.0f},
      .casting_duration = 1.0f,
      .hit_box = (Vector2){20, 20},
  };
}

Mumble GetMumbleProperties(int mumble_id) {
  return mumble_properties[mumble_id];
}
