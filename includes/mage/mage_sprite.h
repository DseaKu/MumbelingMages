#ifndef SPRITE_H
#define SPRITE_H
typedef enum {
  MAGE_INACTIVE = 0,
  MAGE_WALKING,
  MAGE_TAKE_DEMAGE,
  MAGE_DYING,
  MAGE_SPAWNING,
  MAGE_DEAD,
  SIZE_MAGE_STATE_ID,
} MageStateID;

typedef enum {
  MAGE_NONE = 0,
  MAGE,
  SIZE_MAGE_SPRITE_ID,
} MageSpriteID;

#endif // !SPRITE_H
