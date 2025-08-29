#ifndef SPRITE_H
#define SPRITE_H
typedef enum {
  INACTIVE = 0,
  WALK,
  IDLE,
  TAKE_DEMAGE,
  DYING,
  SPAWNING,
  SIZE_STATE_ID,
} StateID;

typedef enum {
  NONE = 0,
  MAGE,
  GOBLIN,
  SKELLETON,
  BAT,
  SIZE_SPRITE_ID,
} SpriteID;
#endif // !SPRITE_H
