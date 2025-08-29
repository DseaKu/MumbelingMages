#ifndef SPRITE_H
#define SPRITE_H
typedef enum {
  INACTIVE = 1 << 0,
  WALK = 1 << 1,
  IDLE = 1 << 2,
  TAKE_DEMAGE = 1 << 3,
  DEAD = 1 << 4,
  SPAWNING = 1 << 5,

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
