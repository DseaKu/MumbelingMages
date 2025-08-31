#ifndef MAGE_SPRITE_H
#define MAGE_SPRITE_H
typedef enum {
  INACTIVE = 0,
  WALKING,
  IDLE,
  TAKE_DEMAGE,
  DYING,
  SIZE_STATE_ID,
} StateID;

typedef enum {
  MAGE,
  SIZE_SPRITE_ID,
} SpriteID;

#endif // !MAGE_SPRITE_H
