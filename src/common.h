#pragma once

#include <pebble.h>

typedef enum ApplicationWindows {
  window_main = 0,
  window_clock,
  application_windows_length
} ApplicationWindows;

typedef enum ApplicationLayers {
  layer_main = 0,
  layer_overlay,
  application_layers_length
} ApplicationLayers;

typedef struct Preferences {

} Preferences;

typedef struct applicationContext {
  Preferences *preferences;
  Window *windows[application_windows_length];
  Layer *layers[application_layers_length];
  struct tm t;

  ApplicationWindows window;
} applicationContext;

