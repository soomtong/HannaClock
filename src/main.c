#include <pebble.h>

enum PNGBitmaps {
  bitmap_plate = 0,
  bitmap_hour_mark,
  bitmap_min_mark,
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
  bitmap_o_clock,
  bitmap_m5,
  bitmap_m10,
  bitmap_m20,
  bitmap_m30,
  bitmap_m40,
  bitmap_m50,
  bitmaps_length
};

enum BitmapLayers {
  layer_plate = 0,
  layer_hour_mark,
  layer_min_mark,
  layer_h1,
  layer_h2,
  layer_h3,
  layer_h4,
  layer_h5,
  layer_h6,
  layer_h7,
  layer_h8,
  layer_h9,
  layer_h10,
  layer_o_clock,
  layer_m5,
  layer_m10,
  layer_m20,
  layer_m30,
  layer_m40,
  layer_m50,
  layers_length
};

static Window *window;
static BitmapLayer *layers[layers_length];
static GBitmap *bitmaps[bitmaps_length];

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  static char s_time_buffer[16];

  strftime(s_time_buffer, sizeof(s_time_buffer), "%I:%M:%S", tick_time);

  APP_LOG(APP_LOG_LEVEL_DEBUG, "called tick hander: %d", units_changed);
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Uptime: %dh %dm %ds", (*tick_time).tm_hour, (*tick_time).tm_min, (*tick_time).tm_sec);

  GRect hide = GRect(0, 0, 0, 0);
  const uint8_t digit_w = 24, digit_h = 26;
  const uint8_t col1 = 2, col2 = 31, col3 = 60, col4 = 89, col5 = 118;
  const uint8_t row1 = 6, row2 = 39, row3 = 72, row4 = 104, row5 = 122;

  // hide digit
  for (int i = 3; i < layers_length; ++i) {
    layer_set_frame(bitmap_layer_get_layer(layers[i]), hide);
  }

  // show digit
  GRect h1 = GRect(col2, row1, digit_w, digit_h);
  layer_set_frame(bitmap_layer_get_layer(layers[layer_h1]), h1);

  GRect h2 = GRect(col1, row2, digit_w, digit_h);
  layer_set_frame(bitmap_layer_get_layer(layers[layer_h2]), h2);

  GRect h3 = GRect(col4, row1, digit_w, digit_h);
  layer_set_frame(bitmap_layer_get_layer(layers[layer_h3]), h3);

  GRect h4 = GRect(col5, row1, digit_w, digit_h);
  layer_set_frame(bitmap_layer_get_layer(layers[layer_h4]), h4);

  GRect h5 = GRect(col3, row1, digit_w, digit_h * 2 + 7);
  layer_set_frame(bitmap_layer_get_layer(layers[layer_h5]), h5);

  GRect h6 = GRect(col2, row2, digit_w * 2 + 5, digit_h);
  layer_set_frame(bitmap_layer_get_layer(layers[layer_h6]), h6);

  GRect h7 = GRect(col4, row2, digit_w * 2 + 5, digit_h);
  layer_set_frame(bitmap_layer_get_layer(layers[layer_h7]), h7);

  GRect h8 = GRect(col1, row3, digit_w * 2 + 5, digit_h);
  layer_set_frame(bitmap_layer_get_layer(layers[layer_h8]), h8);

  GRect h9 = GRect(col3, row3, digit_w * 2 + 5, digit_h);
  layer_set_frame(bitmap_layer_get_layer(layers[layer_h9]), h9);

  GRect h10 = GRect(col1, row1, digit_w, digit_h);
  layer_set_frame(bitmap_layer_get_layer(layers[layer_h10]), h10);

  GRect h11 = GRect(col1, row1, digit_w, digit_h);
  layer_set_frame(bitmap_layer_get_layer(layers[layer_h1]), h11);

  GRect h12 = GRect(col1, row1, digit_w, digit_h);
  layer_set_frame(bitmap_layer_get_layer(layers[layer_h2]), h12);

  GRect hour_mark = GRect(col5, row3, digit_w, digit_h);
  layer_set_frame(bitmap_layer_get_layer(layers[layer_hour_mark]), hour_mark);

  GRect o_clock = GRect(col1, row4, digit_w * 2 + 5, digit_h);
  layer_set_frame(bitmap_layer_get_layer(layers[layer_o_clock]), o_clock);

  // do it (it's not concern other layers, just works)
  layer_mark_dirty(bitmap_layer_get_layer(layers[layer_plate]));
}

static void update_light_layer(Layer *layer, GContext *ctx) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Layer: %p", layer);
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Context: %p", ctx);

  // dummy. no need to perform drawing code
}

static void load_layers(Layer *root_layer) {
  GRect bounds = layer_get_bounds(root_layer);
  GRect hide = GRect(0, 0, 0, 0);

  // set plate
  layers[layer_plate] = bitmap_layer_create(bounds);
  bitmap_layer_set_bitmap(layers[layer_plate], bitmaps[bitmap_plate]);
  layer_add_child(root_layer, bitmap_layer_get_layer(layers[layer_plate]));

  // set layers
  for (int i = 1; i < layers_length; ++i) {
    layers[i] = bitmap_layer_create(hide);
    bitmap_layer_set_bitmap(layers[i], bitmaps[i]);
    layer_add_child(root_layer, bitmap_layer_get_layer(layers[i]));
  }

  layer_set_update_proc(root_layer, update_light_layer);
}

static void unload_layers() {
  for (uint8_t i = 0; i < bitmaps_length; ++i) {
    if (bitmaps[i]) gbitmap_destroy(bitmaps[i]);
  }

  for (uint8_t i = 0; i < layers_length; ++i) {
    if (layers[i]) bitmap_layer_destroy(layers[i]);
  }
}

static void window_load(Window *window) {
  Layer *root_layer = window_get_root_layer(window);

  tick_timer_service_subscribe(HOUR_UNIT | MINUTE_UNIT, tick_handler);

  uint8_t resource_id = (uint8_t)RESOURCE_ID_HANNA_B;

  for (uint8_t i = 0; i < bitmaps_length; ++i) {
    bitmaps[i] = gbitmap_create_with_resource((uint8_t)(resource_id + i));
  }

  load_layers(root_layer);
}

static void window_unload(Window *window) {
  unload_layers();

  tick_timer_service_unsubscribe();
}

static void init(void) {
  window = window_create();
  window_set_window_handlers(window, (WindowHandlers) {
      .load = window_load,
      .unload = window_unload,
  });

  const bool animated = true;
  window_stack_push(window, animated);
}

static void deinit(void) {
  window_destroy(window);
}

int main(void) {
  init();
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Done initializing, pushed window: %p", window);

  app_event_loop();

  deinit();
  return 0;
}
