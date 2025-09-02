#ifndef SPRITE_H
#define SPRITE_H
typedef enum {
  MAGE_INACTIVE = 0,
  MAGE_WALKING,
  MAGE_TAKE_DEMAGE,
  MAGE_DYING,
  MAGE_SPAWNING,
  MAGE_DEAD,
  SIZE_PLAYER_STATE_ID,
} PlayerStateID;

typedef enum {
  PLAYER_NONE = 0,
  MAGE,
  SIZE_PLAYER_SPRITE_ID,
} PlayerSpriteID;

#endif // !SPRITE_H
