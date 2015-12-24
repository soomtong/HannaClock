#include <pebble.h>

#include "clock.h"

static void window_load(Window *window) {
  Layer *root_layer = window_get_root_layer(window);

  if (persist_exists(PERSIST_KEY_ID_POMODORO)) {
    persist_read_data(PERSIST_KEY_ID_POMODORO, &pomodoro, sizeof(pomodoro));
  }
  if (persist_exists(PERSIST_KEY_ID_POMODORO_CYCLE)) {
    persist_read_data(PERSIST_KEY_ID_POMODORO_CYCLE, &pomodoro_cycle, sizeof(pomodoro_cycle));
  }
  if (persist_exists(PERSIST_KEY_ID_POMODORO_CYCLE_NOW)) {
    persist_read_data(PERSIST_KEY_ID_POMODORO_CYCLE_NOW, &pomodoro_cycle_now, sizeof(pomodoro_cycle_now));
  }

  tick_timer_service_subscribe(HOUR_UNIT | MINUTE_UNIT, tick_handler);

  // LOAD RESOURCE
  uint8_t resource_id = (uint8_t)RESOURCE_ID_HANNA_B;

  for (uint8_t i = 0; i < bitmaps_length; ++i) {
    bitmaps[i] = gbitmap_create_with_resource((uint8_t)(resource_id + i));
  }

  load_layers(root_layer);
}

static void window_unload(Window *window) {
  unload_layers();

  persist_write_data(PERSIST_KEY_ID_POMODORO, &pomodoro, sizeof(pomodoro));
  persist_write_data(PERSIST_KEY_ID_POMODORO_CYCLE, &pomodoro_cycle, sizeof(pomodoro_cycle));
  persist_write_data(PERSIST_KEY_ID_POMODORO_CYCLE_NOW, &pomodoro_cycle_now, sizeof(pomodoro_cycle_now));

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

  app_message_register_inbox_received(inbox_received_handler);
  app_message_open(64, 0);
  //app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
}

static void deinit(void) {
  app_message_deregister_callbacks();

  window_destroy(window);
}

int main(void) {
  init();

  app_event_loop();

  deinit();
  return 0;
}
