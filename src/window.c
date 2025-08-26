#include "window.h"
#include <raylib.h>

void ToggleRealFullscreen(int screen_width, int screen_height) {
  int monitor = GetCurrentMonitor();
  if (!IsWindowFullscreen()) {
    SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));
    ToggleFullscreen();
  } else {
    ToggleFullscreen();
    SetWindowSize(screen_width, screen_height);
  }
}
int GetDisplayWidth() {
  if (IsWindowFullscreen()) {
    return GetMonitorWidth(GetCurrentMonitor());
  }
  return GetScreenWidth();
}
int GetDisplayHeigth() {
  if (IsWindowFullscreen()) {
    return GetMonitorHeight(GetCurrentMonitor());
  }
  return GetScreenHeight();
}
