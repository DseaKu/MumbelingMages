
#include "IO_handler.h"

#include <ranlib.h>
#include <raylib.h>
void GetInputs(IO_Flags *io_flags) {

  if (IsKeyReleased(KEY_SPACE)) {
    *io_flags ^= PAUSE_GAME;
  }
  if (IsKeyReleased(KEY_F)) {
    *io_flags ^= TOGGLE_FULLSCREEN;
  }
  if (IsKeyReleased(KEY_E)) {
    *io_flags ^= AUTO_AIM;
  }
  if (IsKeyReleased(KEY_F2)) {
    *io_flags ^= DRAW_DEBUG_INFO;
  }
}
void InitIO_Flags(IO_Flags *io_flags) {

  // *io_flags |= TOGGLE_FULLSCREEN;
  *io_flags |= AUTO_AIM;
}
void DrawDebugText() {}
