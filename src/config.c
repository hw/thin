#include "config.h"

static bool s_arr[NUM_SETTINGS];
static uint32_t s_colors[NUM_COLORS];

void config_init() {
  // Set defaults
  if(!persist_exists(PERSIST_DEFAULTS_SET)) {
    persist_write_bool(PERSIST_DEFAULTS_SET, true);

    persist_write_bool(PERSIST_KEY_DATE, true);
    persist_write_bool(PERSIST_KEY_DAY, true);
    persist_write_bool(PERSIST_KEY_BT, true);
    persist_write_bool(PERSIST_KEY_BATTERY, true);
    persist_write_bool(PERSIST_KEY_SECOND_HAND, true);
    
    persist_write_int(PERSIST_KEY_COLOR_OFFSET + PERSIST_KEY_HOUR_MARKERS_COLOR, 0xFFFFFF);
    persist_write_int(PERSIST_KEY_COLOR_OFFSET + PERSIST_KEY_MINUTE_MARKERS_COLOR, 0xAAAAAA);
    persist_write_int(PERSIST_KEY_COLOR_OFFSET + PERSIST_KEY_CHARGING_MARKERS_COLOR, 0x00FF00);    
    persist_write_int(PERSIST_KEY_COLOR_OFFSET + PERSIST_KEY_HANDS_COLOR, 0xAAAAAA);
    persist_write_int(PERSIST_KEY_COLOR_OFFSET + PERSIST_KEY_TIPS_COLOR, 0xFFFFFF);
    persist_write_int(PERSIST_KEY_COLOR_OFFSET + PERSIST_KEY_SECOND_HAND_COLOR, 0xAA0000);
    persist_write_int(PERSIST_KEY_COLOR_OFFSET + PERSIST_KEY_SECOND_TIP_COLOR, 0xFFFF00);  
    persist_write_int(PERSIST_KEY_COLOR_OFFSET + PERSIST_KEY_CALENDAR_DAY_COLOR, 0xFFFF00);  
  }

  for(int i = 0; i < NUM_SETTINGS; i++) {
    s_arr[i] = persist_read_bool(i);
  }

  for(int j = 0; j < NUM_COLORS; j++) {
    s_colors[j] = persist_read_int(PERSIST_KEY_COLOR_OFFSET + j);
  }
}

bool config_get(int key) {
  return s_arr[key];
}

uint32_t config_get_color(int key) {
  return s_colors[key];
}