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

static Window *window;
static BitmapLayer *plate;
static Layer *overlay;
static GBitmap *bitmaps[bitmaps_length];

static uint8_t prev_hour = 63, prev_min = 63;

static void tick_handler(struct tm *t, TimeUnits units_changed) {
//  static char s_time_buffer[16];
//  strftime(s_time_buffer, sizeof(s_time_buffer), "%I:%M:%S", t);

//  APP_LOG(APP_LOG_LEVEL_DEBUG, "Uptime: %dh %dm %ds, flag: %d", t->tm_hour, t->tm_min, t->tm_sec, units_changed);

  // set clock time
//  uint8_t now_hour = (uint8_t)(*t).tm_hour > 12 ? (uint8_t)(*t).tm_hour - 12 : (uint8_t)(*t).tm_hour;
  int now_hour = t->tm_hour > 12 ? t->tm_hour - 12 : t->tm_hour;  // used less memory than above
  int now_min = t->tm_min / 5;

  // condition for update
  if (prev_hour != (uint8_t)now_hour || prev_min != (uint8_t)now_min) {
    prev_hour = (uint8_t)now_hour;
    prev_min = (uint8_t)now_min;

    layer_mark_dirty(overlay);
  }
}

static void update_light_layer(Layer *layer, GContext *ctx) {
  // set metrics
  const uint8_t digit_w = 24, digit_h = 26;
  const uint8_t col1 = 2, col2 = 31, col3 = 60, col4 = 89, col5 = 118;
  const uint8_t row1 = 6, row2 = 39, row3 = 72, row4 = 104, row5 = 137;

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

  // show hours
  switch (prev_hour) {
    case 0:
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_h2], h2);
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_h10], h10);
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_hour_mark], hour_mark);
      break;
    case 1:
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_h1], h1);
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_hour_mark], hour_mark);
      break;
    case 2:
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_h2], h2);
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_hour_mark], hour_mark);
      break;
    case 3:
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_h3], h3);
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_hour_mark], hour_mark);
      break;
    case 4:
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_h4], h4);
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_hour_mark], hour_mark);
      break;
    case 5:
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_h5], h5);
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_hour_mark], hour_mark);
      break;
    case 6:
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_h6], h6);
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_hour_mark], hour_mark);
      break;
    case 7:
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_h7], h7);
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_hour_mark], hour_mark);
      break;
    case 8:
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_h8], h8);
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_hour_mark], hour_mark);
      break;
    case 9:
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_h9], h9);
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_hour_mark], hour_mark);
      break;
    case 10:
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_h10], h10);
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_hour_mark], hour_mark);
      break;
    case 11:
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_h1], h1);
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_h10], h10);
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_hour_mark], hour_mark);
      break;
    case 12:
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_h2], h2);
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_h10], h10);
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_hour_mark], hour_mark);
      break;
    default:
      break;
  }


  // show minutes
  switch (prev_min) {
    case 0:
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_o_clock], o_clock);
      break;
    case 1:
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_m5], m5);
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_min_mark], min_mark);
      break;
    case 2:
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_m10], m10);
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_min_mark], min_mark);
      break;
    case 3:
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_m10], m10);
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_m5], m5);
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_min_mark], min_mark);
      break;
    case 4:
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_m20], m20);
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_m10], m10_2);
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_min_mark], min_mark);
      break;
    case 5:
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_m20], m20);
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_m10], m10_2);
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_m5], m5);
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_min_mark], min_mark);
      break;
    case 6:
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_m30], m30);
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_m10], m10);
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_min_mark], min_mark);
      break;
    case 7:
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_m30], m30);
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_m10], m10);
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_m5], m5);
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_min_mark], min_mark);
      break;
    case 8:
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_m40], m40);
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_m10_2], m10_2);
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_min_mark], min_mark);
      break;
    case 9:
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_m40], m40);
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_m10_2], m10_2);
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_m5], m5);
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_min_mark], min_mark);
      break;
    case 10:
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_m50], m50);
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_m10_2], m10_2);
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_min_mark], min_mark);
      break;
    case 11:
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_m5], m5);
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_m50], m50);
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_m10_2], m10_2);
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_min_mark], min_mark);
      break;
    case 12:
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_o_clock], o_clock);
      break;
    default:
      break;
  }
}

static void load_layers(Layer *root_layer) {
  GRect bounds = layer_get_bounds(root_layer);

  // set plate
  plate = bitmap_layer_create(bounds);
  overlay = layer_create(bounds);

  bitmap_layer_set_bitmap(plate, bitmaps[bitmap_plate]);

  layer_add_child(root_layer, bitmap_layer_get_layer(plate));
  layer_add_child(root_layer, overlay);

  layer_set_update_proc(overlay, update_light_layer);
}

static void unload_layers() {
  for (uint8_t i = 0; i < bitmaps_length; ++i) {
    if (bitmaps[i]) gbitmap_destroy(bitmaps[i]);
  }

  layer_destroy(overlay);
  bitmap_layer_destroy(plate);
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
