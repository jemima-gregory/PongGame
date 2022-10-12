#ifndef BAT_H
#define BAT_H

#include <stdint.h>

typedef struct
{
    int8_t position;
} Bat_t;

Bat_t bat_init (void);

void display_bat(Bat_t bat);

Bat_t check_navswitch(Bat_t bat);

#endif