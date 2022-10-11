#ifndef BAT_H
#define BAT_H

#include "stdint.h"

int8_t init_bat(void);

void display_bat(int8_t bat);

void check_navswitch(void);

#endif