#pragma once

#include "globals.h"

void config_init();

bool config_get(int key);
uint32_t config_get_color(int key);
