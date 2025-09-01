#include "core/window.h"
#include <raylib.h>

void ToggleRealFullscreen() {
  if (!IsWindowFullscreen()) {
    int monitor = GetCurrentMonitor();
    SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));
  }
  ToggleFullscreen();
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
