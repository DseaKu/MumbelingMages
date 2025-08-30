#ifndef SPRITE_H
#define SPRITE_H
typedef enum {
  INACTIVE = 0,
  WALKING,
  IDLE,
  TAKE_DEMAGE,
  DYING,
  SPAWNING,
  DEAD,
  PROCESSES_ACTING_FORCES,
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

// typedef enum{
//   GOBLIN,
//   SKELLETON,
//   BAT,
//   SIZE_SPRITE_ID,
//
//
//
// } EnemySpriteID;

typedef enum {
  FIREBALL,
  ICELANCE,
  BLIZZARD,

} SpellSpriteID;
#endif // !SPRITE_H
