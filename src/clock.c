#include <pebble.h>

#include "clock.h"

Window *window = NULL;
Layer *overlay = NULL;
BitmapLayer *plate = NULL;
GBitmap *bitmaps[bitmaps_length] = {NULL};

Pomodoro pomodoro = {.mode = 0, .cycle = 0, .cycle_now = 0, .timer = -1};

uint8_t prev_hour = 63, prev_min = 63; // just 2^6 last number

const uint32_t const pomodoro_segments[] = { 1000, 500, 1000, 500, 1000 };
const uint32_t const rest_segments[] = { 400, 500, 800, 500, 400, 500, 800, 500, 400 };
const uint32_t const end_segments[] = { 100, 200, 100 };

VibePattern pat1 = {
    .durations = pomodoro_segments,
    .num_segments = ARRAY_LENGTH(pomodoro_segments),
};
VibePattern pat2 = {
    .durations = rest_segments,
    .num_segments = ARRAY_LENGTH(rest_segments),
};
VibePattern pat3 = {
    .durations = end_segments,
    .num_segments = ARRAY_LENGTH(end_segments),
};


void update_rect_light_layer(Layer *layer, GContext *ctx) {
  // set metrics
  const GSize digit = {24, 26};
  const uint8_t col_pad = 29, row_pad = 33;
  const uint8_t col1 = 2, col2 = col1 + col_pad, col3 = col2 + col_pad, col4 = col3 + col_pad, col5 = col4 + col_pad;
  const uint8_t row1 = 5, row2 = row1 + row_pad, row3 = row2 + row_pad, row4 = row3 + row_pad, row5 = row4 + row_pad;

  const GRect h1 = GRect(col2, row1, digit.w, digit.h);
  const GRect h2 = GRect(col1, row2, digit.w, digit.h);
  const GRect h3 = GRect(col4, row1, digit.w, digit.h);
  const GRect h4 = GRect(col5, row1, digit.w, digit.h);
  const GRect h5 = GRect(col3, row1, digit.w, (int16_t) (digit.h * 2 + 7));
  const GRect h6 = GRect(col2, row2, (int16_t) (digit.w * 2 + 5), digit.h);
  const GRect h7 = GRect(col4, row2, (int16_t) (digit.w * 2 + 5), digit.h);
  const GRect h8 = GRect(col1, row3, (int16_t) (digit.w * 2 + 5), digit.h);
  const GRect h9 = GRect(col3, row3, (int16_t) (digit.w * 2 + 5), digit.h);
  const GRect h10 = GRect(col1, row1, digit.w, digit.h);
  const GRect hour_mark = GRect(col5, row3, digit.w, digit.h);

  const GRect o_clock = GRect(col1, row4, (int16_t) (digit.w * 2 + 5), digit.h);
  const GRect m5 = GRect(col4, row5, digit.w, digit.h);
  const GRect m10 = GRect(col5, row4, digit.w, digit.h);
  const GRect m10_2 = GRect(col3, row5, digit.w, digit.h);
  const GRect m20 = GRect(col3, row4, digit.w, digit.h);
  const GRect m30 = GRect(col4, row4, digit.w, digit.h);
  const GRect m40 = GRect(col1, row5, digit.w, digit.h);
  const GRect m50 = GRect(col2, row5, digit.w, digit.h);
  const GRect min_mark = GRect(col5, row5, digit.w, digit.h);

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

void update_round_light_layer(Layer *layer, GContext *ctx) {
  // set metrics
  const GSize digit = {24, 26};
  const uint8_t col_pad = 25, row_pad = 33, start_col = 81;
  const uint8_t col1 = 1, col2 = col1 + col_pad, col3 = col2 + col_pad, col4 = col3 + col_pad + 3,
      col5 = col4 + col_pad, col6 = col5 + col_pad + 1, col7 = col6 + col_pad;
  const int16_t row0 = 9, row1 = row0 - row_pad, row2 = row1 - row_pad, row3 = row2 - row_pad, row4 = row3 - row_pad,
      row5 = row4 - row_pad, row6 = row5 - row_pad, row7 = row6 - row_pad, row8 = row7 - row_pad,
      row9 = row8 - row_pad, row10 = row9 - row_pad, row11 = row10 - row_pad, row12 = row11 - row_pad;

  const GSize hour_plate = GSize(80, 524);
  const GSize min_plate = GSize(100, 524);

  const GRect hour_mark = (GRect) {{col3, 77}, .size = digit};

  // show hours
  switch (prev_hour) {
    case 0:
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_plate_round_h], (GRect) {{0, row11}, hour_plate});
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_h10], (GRect) {{col1, 77}, .size = digit});
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_h2], (GRect) {{col2, 77}, .size = digit});
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_hour_mark], hour_mark);
      break;
    case 1:
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_plate_round_h], (GRect) {{0, row0}, hour_plate});
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_h1], (GRect) {{col2, 77}, .size = digit});
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_hour_mark], hour_mark);
      break;
    case 2:
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_plate_round_h], (GRect) {{0, row1}, hour_plate});
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_h2], (GRect) {{col2, 77}, .size = digit});
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_hour_mark], hour_mark);
      break;
    case 3:
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_plate_round_h], (GRect) {{0, row2}, hour_plate});
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_h3], (GRect) {{col2, 77}, .size = digit});
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_hour_mark], hour_mark);
      break;
    case 4:
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_plate_round_h], (GRect) {{0, row3}, hour_plate});
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_h4], (GRect) {{col2, 77}, .size = digit});
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_hour_mark], hour_mark);
      break;
    case 5:
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_plate_round_h], (GRect) {{0, row4}, hour_plate});
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_h5], (GRect) {{col1, 77}, .size = {(int16_t) (digit.w * 2 + 2), digit.h}});
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_hour_mark], hour_mark);
      break;
    case 6:
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_plate_round_h], (GRect) {{0, row5}, hour_plate});
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_h6], (GRect) {{col1, 77}, .size = {(int16_t) (digit.w * 2 + 2), digit.h}});
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_hour_mark], hour_mark);
      break;
    case 7:
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_plate_round_h], (GRect) {{0, row6}, hour_plate});
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_h7], (GRect) {{col1, 77}, .size = {(int16_t) (digit.w * 2 + 2), digit.h}});
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_hour_mark], hour_mark);
      break;
    case 8:
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_plate_round_h], (GRect) {{0, row7}, hour_plate});
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_h8], (GRect) {{col1, 77}, .size = {(int16_t) (digit.w * 2 + 2), digit.h}});
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_hour_mark], hour_mark);
      break;
    case 9:
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_plate_round_h], (GRect) {{0, row8}, hour_plate});
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_h9], (GRect) {{col1, 77}, .size = {(int16_t) (digit.w * 2 + 2), digit.h}});
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_hour_mark], hour_mark);
      break;
    case 10:
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_plate_round_h], (GRect) {{0, row9}, hour_plate});
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_h10], (GRect) {{col2, 77}, .size = digit});
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_hour_mark], hour_mark);
      break;
    case 11:
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_plate_round_h], (GRect) {{0, row10}, hour_plate});
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_h10], (GRect) {{col1, 77}, .size = digit});
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_h1], (GRect) {{col2, 77}, .size = digit});
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_hour_mark], hour_mark);
      break;
    case 12:
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_plate_round_h], (GRect) {{0, row11}, hour_plate});
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_h10], (GRect) {{col1, 77}, .size = digit});
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_h2], (GRect) {{col2, 77}, .size = digit});
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_hour_mark], hour_mark);
      break;
    default:
      break;
  }

  // show minutes
  switch (prev_min) {
    case 0:
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_plate_round_m], (GRect) {{start_col, row0}, min_plate});
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_o_clock], (GRect) {.origin = {col4, 77}, .size = {(int16_t) (digit.w * 2 + 2), digit.h}});
      break;
    case 1: // 5분
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_plate_round_m], (GRect) {{start_col, row1}, min_plate});
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_m5], (GRect) {{col4, 77}, digit});
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_min_mark], (GRect) {{col5, 77}, digit});
      break;
    case 2:
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_plate_round_m], (GRect) {{start_col, row2}, min_plate});
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_m10], (GRect) {{col4, 77}, digit});
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_min_mark], (GRect) {{col5, 77}, digit});
      break;
    case 3: // 15
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_plate_round_m], (GRect) {{start_col, row3}, min_plate});
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_m10], (GRect) {{col4, 77}, digit});
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_m5], (GRect) {{col5, 77}, digit});
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_min_mark], (GRect) {{col6, 77}, digit});
      break;
    case 4:
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_plate_round_m], (GRect) {{start_col, row4}, min_plate});
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_m20], (GRect) {{col4, 77}, digit});
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_m10], (GRect) {{col5, 77}, digit});
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_min_mark], (GRect) {{col6, 77}, digit});
      break;
    case 5: // 25
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_plate_round_m], (GRect) {{start_col, row5}, min_plate});
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_m20], (GRect) {{col4, 77}, digit});
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_m10], (GRect) {{col5, 77}, digit});
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_m5], (GRect) {{col6, 77}, digit});
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_min_mark], (GRect) {{col7, 77}, digit});
      break;
    case 6:
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_plate_round_m], (GRect) {{start_col, row6}, min_plate});
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_m30], (GRect) {{col4, 77}, digit});
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_m10], (GRect) {{col5, 77}, digit});
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_min_mark], (GRect) {{col6, 77}, digit});
      break;
    case 7: // 35
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_plate_round_m], (GRect) {{start_col, row7}, min_plate});
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_m30], (GRect) {{col4, 77}, digit});
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_m10], (GRect) {{col5, 77}, digit});
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_m5], (GRect) {{col6, 77}, digit});
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_min_mark], (GRect) {{col7, 77}, digit});
      break;
    case 8:
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_plate_round_m], (GRect) {{start_col, row8}, min_plate});
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_m40], (GRect) {{col4, 77}, digit});
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_m10_2], (GRect) {{col5, 77}, digit});
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_min_mark], (GRect) {{col6, 77}, digit});
      break;
    case 9: //45
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_plate_round_m], (GRect) {{start_col, row9}, min_plate});
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_m40], (GRect) {{col4, 77}, digit});
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_m10_2], (GRect) {{col5, 77}, digit});
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_m5], (GRect) {{col6, 77}, digit});
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_min_mark], (GRect) {{col7, 77}, digit});
      break;
    case 10:
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_plate_round_m], (GRect) {{start_col, row10}, min_plate});
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_m50], (GRect) {{col4, 77}, digit});
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_m10_2], (GRect) {{col5, 77}, digit});
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_min_mark], (GRect) {{col6, 77}, digit});
      break;
    case 11: // 55
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_plate_round_m], (GRect) {{start_col, row11}, min_plate});
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_m50], (GRect) {{col4, 77}, digit});
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_m10_2], (GRect) {{col5, 77}, digit});
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_m5], (GRect) {{col6, 77}, digit});
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_min_mark], (GRect) {{col7, 77}, digit});
      break;
    case 12:
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_plate_round_m], (GRect) {{start_col, row12}, min_plate});
      graphics_draw_bitmap_in_rect(ctx, bitmaps[bitmap_o_clock], (GRect) {.origin = {col4, 77}, .size = {(int16_t) (digit.w * 2 + 2), digit.h}});
      break;
    default:
      break;
  }
}

void tick_handler(struct tm *t, TimeUnits units_changed) {
  // SET CLOCK TIME
  int now_hour = t->tm_hour > 12 ? t->tm_hour - 12 : t->tm_hour;  // used less memory than above
  int now_min = t->tm_min / 5;

  // condition for update
  if (prev_hour != (uint8_t)now_hour || prev_min != (uint8_t)now_min) {
    prev_hour = (uint8_t)now_hour;
    prev_min = (uint8_t)now_min;

    layer_mark_dirty(overlay);

    // feedback by options
    if (pomodoro.mode) {
      if (pomodoro.cycle > pomodoro.cycle_now) {
        pomodoro.timer++;
        //APP_LOG(APP_LOG_LEVEL_INFO, "feedback_pomodoro.mode: %d, feedback_pomodoro.cycle: %d, feedback_pomodoro.cycle_now: %d ", pomodoro.mode, pomodoro.cycle, pomodoro.cycle_now);

        // pomodoro.timer == 0, 5, 6, 11
        int8_t check = (int8_t) (pomodoro.timer % 6);

        //APP_LOG(APP_LOG_LEVEL_INFO, "check: %d", check);

        switch (check) {
          case 0:   // start pomodoro
            vibes_enqueue_custom_pattern(pat1);

            //APP_LOG(APP_LOG_LEVEL_INFO, "go pomodoro: %d", pomodoro.cycle_now);

            break;
          case 5:   // rest pomodoro
            pomodoro.cycle_now++;
            vibes_enqueue_custom_pattern(pat2);

            //APP_LOG(APP_LOG_LEVEL_INFO, "take rest: %d", pomodoro.cycle_now);
            break;
          default:
            break;
        }
      }
    }
  }
}

void inbox_received_handler(DictionaryIterator *iter, void *context) {
  // get preference
  Tuple *pomodoro_t = dict_find(iter, KEY_FEEDBACK_POMODORO);
  Tuple *pomodoro_cycle_t = dict_find(iter, KEY_FEEDBACK_POMODORO_CYCLE);

  if(pomodoro_t && pomodoro_t->value->int8 > -1 && pomodoro_cycle_t && pomodoro_cycle_t->value->int8 > -1) {
    pomodoro.mode = pomodoro_t->value->int8;
    pomodoro.cycle = pomodoro_cycle_t->value->int8;

    if (pomodoro.mode && pomodoro.cycle_now == 0) { // init pomodoro
      //APP_LOG(APP_LOG_LEVEL_INFO, "init pomodoro: %d / %d", pomodoro.cycle, pomodoro.cycle_now);

      vibes_long_pulse();
    } else {
      pomodoro.cycle_now = 0;
      pomodoro.timer = -1;

      vibes_enqueue_custom_pattern(pat3);

      persist_write_data(PERSIST_KEY_ID_POMODORO, &pomodoro.mode, sizeof(pomodoro.mode));
      persist_write_data(PERSIST_KEY_ID_POMODORO_CYCLE, &pomodoro.cycle, sizeof(pomodoro.cycle));
      persist_write_data(PERSIST_KEY_ID_POMODORO_CYCLE_NOW, &pomodoro.cycle_now, sizeof(pomodoro.cycle_now));
    }
  }
}

void load_layers(Layer *root_layer) {
  GRect bounds = layer_get_bounds(root_layer);

  // set plate
  plate = bitmap_layer_create(bounds);
  overlay = layer_create(bounds);

  bitmap_layer_set_bitmap(plate, bitmaps[bitmap_plate]);

  layer_add_child(root_layer, bitmap_layer_get_layer(plate));
  layer_add_child(root_layer, overlay);

  // Conditionally print out the shape of the display
  //APP_LOG(APP_LOG_LEVEL_INFO, "This is a %s display!", PBL_IF_RECT_ELSE("rectangular", "round"));

#if defined(PBL_ROUND)
  layer_set_update_proc(overlay, update_round_light_layer);
#else
  layer_set_update_proc(overlay, update_rect_light_layer);
#endif
}

void unload_layers() {
  // UNLOAD RESOURCE
  for (uint8_t i = 0; i < bitmaps_length; ++i) {
    if (bitmaps[i]) gbitmap_destroy(bitmaps[i]);
  }

  layer_destroy(overlay);
  bitmap_layer_destroy(plate);
}
