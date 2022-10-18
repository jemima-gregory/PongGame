/*
    File:    bat.h
    Authors: Jemima Gregory, Jee Park
    Date:    11 October 2022
    Descr:   Functionality of the bat object, its movement, control via the navswitch, and its display
*/

#ifndef BAT_H
#define BAT_H

#include <stdint.h>

/** The bat structure */
typedef struct
{
    int8_t position;
} Bat_t;

/** Initialise the bat object - is called when the game begins, 
    so the bat is initiated with the same start position 
    each time, 3, "the middle".
    @return the new bat object */
Bat_t bat_init (void);

/** Display the bat on the led matrix 
    @param the current bat object */
void bat_display (Bat_t bat);

/** Checks if the nav switch has been pressed and move the bat position accordingly 
    @param the current bat object 
    @return the new bat object with updated position */
Bat_t bat_update_position (Bat_t bat);

#endif