#include <pebble.h>

enum PNGBitmaps {
  bitmap_plate = 0,
  bitmap_hour_mark,
  bitmap_min_mark,
  bitmaps_length
};

enum BitmapLayers {
  layer_plate = 0,
  layer_hour_mark,
  layer_min_mark,
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

  // draw new crop area
  GRect origin = GRect(0, 0, 0, 0);
  GRect hour = GRect(116, 70, 28, 31);
  GRect min = GRect(116, 135, 28, 33);

  layer_set_frame(bitmap_layer_get_layer(layers[layer_hour_mark]), hour);

  // do it
  layer_mark_dirty(bitmap_layer_get_layer(layers[layer_hour_mark]));
}

static void update_light_layer(Layer *layer, GContext *ctx) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Layer: %p", layer);
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Context: %p", ctx);

  // dummy. no need to perform drawing code
}

static void load_layers(Layer *root_layer) {
  GRect bounds = layer_get_bounds(root_layer);

  // set plate
  layers[layer_plate] = bitmap_layer_create(bounds);
  bitmap_layer_set_bitmap(layers[layer_plate], bitmaps[bitmap_plate]);
  layer_add_child(root_layer, bitmap_layer_get_layer(layers[layer_plate]));

  // set hour
  GRect hour = GRect(116, 70, 28, 31);
  layers[layer_hour_mark] = bitmap_layer_create(hour);
  bitmap_layer_set_bitmap(layers[layer_hour_mark], bitmaps[bitmap_hour_mark]);
  layer_add_child(root_layer, bitmap_layer_get_layer(layers[layer_hour_mark]));

  // set min
  GRect min = GRect(116, 135, 28, 33);
  layers[layer_min_mark] = bitmap_layer_create(min);
  bitmap_layer_set_bitmap(layers[layer_min_mark], bitmaps[bitmap_min_mark]);
  layer_add_child(root_layer, bitmap_layer_get_layer(layers[layer_min_mark]));


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

  uint8_t resource_id = (uint8_t)RESOURCE_ID_HANNA_1;

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
