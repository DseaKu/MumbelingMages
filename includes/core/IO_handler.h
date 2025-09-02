#ifndef IO_HANDLER_H
#define IO_HANDLER_H

#include <raylib.h>
#include <stdint.h>
typedef enum {
  GAME_OVER = 1 << 0,
  PAUSE_GAME = 1 << 1,
  AUTO_AIM = 1 << 2,
  DRAW_DEBUG_INFO = 1 << 3,
  TOGGLE_FULLSCREEN = 1 << 4,
  IS_MOUSE_LEFT_PRESSED = 1 << 5,
} IO_Flags_Definition;

typedef uint64_t IO_Flags;

void InitIO_Flags(IO_Flags *io_flags);
void GetInputs(IO_Flags *io_flags);
void DrawDebugText();

#endif // !IO_HANDLER_H
