#pragma once

#include <pebble.h>

#define KEY_FEEDBACK_POMODORO 0
#define KEY_FEEDBACK_POMODORO_CYCLE 1
#define PERSIST_KEY_ID_POMODORO 1
#define PERSIST_KEY_ID_POMODORO_CYCLE 2
#define PERSIST_KEY_ID_POMODORO_CYCLE_NOW 3

// pair bitmaps with layers for just convenience
enum PNGBitmaps {
  bitmap_plate = 0,
  bitmap_hour_mark,
  bitmap_h1,
  bitmap_h2,
  bitmap_h3,
  bitmap_h4,
  bitmap_h5,
  bitmap_h6,
  bitmap_h7,
  bitmap_h8,
  bitmap_h9,
  bitmap_h10,
  bitmap_min_mark,
  bitmap_o_clock,
  bitmap_m5,
  bitmap_m10,
  bitmap_m20,
  bitmap_m30,
  bitmap_m40,
  bitmap_m50,
  bitmap_m10_2,
  bitmap_plate_round_h,
  bitmap_plate_round_m,
  bitmaps_length
};

typedef struct Pomodoro {
  int8_t mode, cycle, cycle_now, timer;
} Pomodoro;

extern Window *window;
extern Layer *overlay;
extern BitmapLayer *plate;
extern GBitmap *bitmaps[bitmaps_length];
extern Pomodoro pomodoro;

void update_rect_light_layer(Layer *layer, GContext *ctx);

void update_round_light_layer(Layer *layer, GContext *ctx);

void tick_handler(struct tm *t, TimeUnits units_changed);

void inbox_received_handler(DictionaryIterator *iter, void *context);

void load_layers(Layer *root_layer);

void unload_layers();