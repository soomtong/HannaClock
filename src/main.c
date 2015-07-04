#include <pebble.h>

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
  bitmaps_length
};

enum BitmapLayers {
  layer_plate = 0,
  layer_hour_mark,
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
  layer_min_mark,
  layer_o_clock,
  layer_m5,
  layer_m10,
  layer_m20,
  layer_m30,
  layer_m40,
  layer_m50,
  layer_m10_2,
  layers_length
};

static Window *window;
static BitmapLayer *layers[layers_length];
static GBitmap *bitmaps[bitmaps_length];

static uint8_t prev_hour = 63, prev_min = 63;

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
//  static char s_time_buffer[16];
//  strftime(s_time_buffer, sizeof(s_time_buffer), "%I:%M:%S", tick_time);

  APP_LOG(APP_LOG_LEVEL_DEBUG, "Uptime: %dh %dm %ds, flag: %d", (*tick_time).tm_hour, (*tick_time).tm_min, (*tick_time).tm_sec, units_changed);

  // set metrics
  const uint8_t digit_w = 24, digit_h = 26;
  const uint8_t col1 = 2, col2 = 31, col3 = 60, col4 = 89, col5 = 118;
  const uint8_t row1 = 6, row2 = 39, row3 = 72, row4 = 104, row5 = 137;

  const GRect hide = GRect(0, 0, 0, 0);
  const GRect h1 = GRect(col2, row1, digit_w, digit_h);
  const GRect h2 = GRect(col1, row2, digit_w, digit_h);
  const GRect h3 = GRect(col4, row1, digit_w, digit_h);
  const GRect h4 = GRect(col5, row1, digit_w, digit_h);
  const GRect h5 = GRect(col3, row1, digit_w, digit_h * 2 + 7);
  const GRect h6 = GRect(col2, row2, digit_w * 2 + 5, digit_h);
  const GRect h7 = GRect(col4, row2, digit_w * 2 + 5, digit_h);
  const GRect h8 = GRect(col1, row3, digit_w * 2 + 5, digit_h);
  const GRect h9 = GRect(col3, row3, digit_w * 2 + 5, digit_h);
  const GRect h10 = GRect(col1, row1, digit_w, digit_h);
  const GRect hour_mark = GRect(col5, row3, digit_w, digit_h);

  const GRect o_clock = GRect(col1, row4, digit_w * 2 + 5, digit_h);
  const GRect m5 = GRect(col4, row5, digit_w, digit_h);
  const GRect m10 = GRect(col5, row4, digit_w, digit_h);
  const GRect m10_2 = GRect(col3, row5, digit_w, digit_h);
  const GRect m20 = GRect(col3, row4, digit_w, digit_h);
  const GRect m30 = GRect(col4, row4, digit_w, digit_h);
  const GRect m40 = GRect(col1, row5, digit_w, digit_h);
  const GRect m50 = GRect(col2, row5, digit_w, digit_h);
  const GRect min_mark = GRect(col5, row5, digit_w, digit_h);

  bool mark_redraw = false;

  // set clock time
  //uint8_t now_hour = (uint8_t)(*tick_time).tm_hour > 12 ? (uint8_t)(*tick_time).tm_hour - 12 : (uint8_t)(*tick_time).tm_hour;
  int now_hour = (*tick_time).tm_hour > 12 ? (*tick_time).tm_hour - 12 : (*tick_time).tm_hour;  // used less memory than above
  int now_min = (*tick_time).tm_min / 5;

  APP_LOG(APP_LOG_LEVEL_DEBUG, "clock time prev: %d, %d", prev_hour, prev_min);
  APP_LOG(APP_LOG_LEVEL_DEBUG, "clock time now: %d, %d", now_hour, now_min);

  // condition for update
  if (prev_hour != (uint8_t)now_hour) {

    mark_redraw = true;
    prev_hour = (uint8_t)now_hour;

    // hide hour digit
    for (int i = 2; i < 12; ++i) {
      layer_set_frame(bitmap_layer_get_layer(layers[i]), hide);
    }

    // show hours
    switch (now_hour) {
      case 0:
        layer_set_frame(bitmap_layer_get_layer(layers[layer_h1]), h1);
        layer_set_frame(bitmap_layer_get_layer(layers[layer_h10]), h10);
        break;
      case 1:
        layer_set_frame(bitmap_layer_get_layer(layers[layer_h1]), h1);
        break;
      case 2:
        layer_set_frame(bitmap_layer_get_layer(layers[layer_h2]), h2);
        break;
      case 3:
        layer_set_frame(bitmap_layer_get_layer(layers[layer_h3]), h3);
        break;
      case 4:
        layer_set_frame(bitmap_layer_get_layer(layers[layer_h4]), h4);
        break;
      case 5:
        layer_set_frame(bitmap_layer_get_layer(layers[layer_h5]), h5);
        break;
      case 6:
        layer_set_frame(bitmap_layer_get_layer(layers[layer_h6]), h6);
        break;
      case 7:
        layer_set_frame(bitmap_layer_get_layer(layers[layer_h7]), h7);
        break;
      case 8:
        layer_set_frame(bitmap_layer_get_layer(layers[layer_h8]), h8);
        break;
      case 9:
        layer_set_frame(bitmap_layer_get_layer(layers[layer_h9]), h9);
        break;
      case 10:
        layer_set_frame(bitmap_layer_get_layer(layers[layer_h10]), h10);
        break;
      case 11:
        layer_set_frame(bitmap_layer_get_layer(layers[layer_h1]), h1);
        layer_set_frame(bitmap_layer_get_layer(layers[layer_h10]), h10);
        break;
      case 12:
        layer_set_frame(bitmap_layer_get_layer(layers[layer_h2]), h2);
        layer_set_frame(bitmap_layer_get_layer(layers[layer_h10]), h10);
        break;
      default:
        break;
    }

    // hour mark
    layer_set_frame(bitmap_layer_get_layer(layers[layer_hour_mark]), hour_mark);
  }

  if (prev_min != (uint8_t)now_min) {

    mark_redraw = true;
    prev_min = (uint8_t)now_min;

    // hide min digit
    for (int i = 12; i < layers_length; ++i) {
      layer_set_frame(bitmap_layer_get_layer(layers[i]), hide);
    }

    // show minutes
    switch (now_min) {
      case 0:
        layer_set_frame(bitmap_layer_get_layer(layers[layer_o_clock]), o_clock);
        break;
      case 1:
        layer_set_frame(bitmap_layer_get_layer(layers[layer_m5]), m5);
        layer_set_frame(bitmap_layer_get_layer(layers[layer_min_mark]), min_mark);
        break;
      case 2:
        layer_set_frame(bitmap_layer_get_layer(layers[layer_m10]), m10);
        layer_set_frame(bitmap_layer_get_layer(layers[layer_min_mark]), min_mark);
        break;
      case 3:
        layer_set_frame(bitmap_layer_get_layer(layers[layer_m10]), m10);
        layer_set_frame(bitmap_layer_get_layer(layers[layer_m5]), m5);
        layer_set_frame(bitmap_layer_get_layer(layers[layer_min_mark]), min_mark);
        break;
      case 4:
        layer_set_frame(bitmap_layer_get_layer(layers[layer_m20]), m20);
        layer_set_frame(bitmap_layer_get_layer(layers[layer_m10]), m10_2);
        layer_set_frame(bitmap_layer_get_layer(layers[layer_min_mark]), min_mark);
        break;
      case 5:
        layer_set_frame(bitmap_layer_get_layer(layers[layer_m20]), m20);
        layer_set_frame(bitmap_layer_get_layer(layers[layer_m10]), m10_2);
        layer_set_frame(bitmap_layer_get_layer(layers[layer_m5]), m5);
        layer_set_frame(bitmap_layer_get_layer(layers[layer_min_mark]), min_mark);
        break;
      case 6:
        layer_set_frame(bitmap_layer_get_layer(layers[layer_m30]), m30);
        layer_set_frame(bitmap_layer_get_layer(layers[layer_m10]), m10);
        layer_set_frame(bitmap_layer_get_layer(layers[layer_min_mark]), min_mark);
        break;
      case 7:
        layer_set_frame(bitmap_layer_get_layer(layers[layer_m30]), m30);
        layer_set_frame(bitmap_layer_get_layer(layers[layer_m10]), m10);
        layer_set_frame(bitmap_layer_get_layer(layers[layer_m5]), m5);
        layer_set_frame(bitmap_layer_get_layer(layers[layer_min_mark]), min_mark);
        break;
      case 8:
        layer_set_frame(bitmap_layer_get_layer(layers[layer_m40]), m40);
        layer_set_frame(bitmap_layer_get_layer(layers[layer_m10_2]), m10_2);
        layer_set_frame(bitmap_layer_get_layer(layers[layer_min_mark]), min_mark);
        break;
      case 9:
        layer_set_frame(bitmap_layer_get_layer(layers[layer_m40]), m40);
        layer_set_frame(bitmap_layer_get_layer(layers[layer_m10_2]), m10_2);
        layer_set_frame(bitmap_layer_get_layer(layers[layer_m5]), m5);
        layer_set_frame(bitmap_layer_get_layer(layers[layer_min_mark]), min_mark);
        break;
      case 10:
        layer_set_frame(bitmap_layer_get_layer(layers[layer_m50]), m50);
        layer_set_frame(bitmap_layer_get_layer(layers[layer_m10_2]), m10_2);
        layer_set_frame(bitmap_layer_get_layer(layers[layer_min_mark]), min_mark);
        break;
      case 11:
        layer_set_frame(bitmap_layer_get_layer(layers[layer_m5]), m5);
        layer_set_frame(bitmap_layer_get_layer(layers[layer_m50]), m50);
        layer_set_frame(bitmap_layer_get_layer(layers[layer_m10_2]), m10_2);
        layer_set_frame(bitmap_layer_get_layer(layers[layer_min_mark]), min_mark);
        break;
      case 12:
        layer_set_frame(bitmap_layer_get_layer(layers[layer_o_clock]), o_clock);
        break;
      default:
        break;
    }
  }

  // do it (it's not concern other layers, just works)
  if (mark_redraw) {
    APP_LOG(APP_LOG_LEVEL_DEBUG, "=== Layer: Redraw!");
    layer_mark_dirty(bitmap_layer_get_layer(layers[layer_plate]));
  }
}

static void update_light_layer(Layer *layer, GContext *ctx) {
//  APP_LOG(APP_LOG_LEVEL_DEBUG, "Layer: %p", layer);
//  APP_LOG(APP_LOG_LEVEL_DEBUG, "Context: %p", ctx);

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
