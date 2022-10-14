#ifndef BAT_H
#define BAT_H

#include <stdint.h>

typedef struct
{
    int8_t position;
} Bat_t;

// Initialize bat
Bat_t bat_init (void);

//Display the bat on the led matrix
void bat_display (Bat_t bat);

// Checks if the nav switch has been pressed and moves the bat position accordingly
Bat_t bat_update_position (Bat_t bat);

#endif