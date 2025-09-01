
#include "core/IO_handler.h"

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
  if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
    *io_flags ^= IS_MOUSE_LEFT_PRESSED;
  }
}
void InitIO_Flags(IO_Flags *io_flags) {

  // *io_flags |= TOGGLE_FULLSCREEN;
  *io_flags |= AUTO_AIM;
}
void DrawDebugText() {}
