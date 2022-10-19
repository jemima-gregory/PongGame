/*
    File:    bat.c
    Authors: Jemima Gregory, Jee Park
    Date:    11 October 2022
    Descr:   Functionality of the bat object, its movement, control via the navswitch, and its display
*/

#include "system.h"
#include "navswitch.h"
#include "bat.h"
#include "tinygl.h"


/** The map the for led matrix (use to calculate coord for tinygl)
    ------y------
    6 5 4 3 2 1 0
    o o o o o o o 0  |
    o o o o o o o 1  |
    o o o o o o o 2  x
    o o o o o o o 3  |
    o o o o o o o 4  | */

/** Initialise the bat object - is called when the game begins, 
    so the bat is initiated with the same start position 
    each time, 3, "the middle".
    @return the new bat object */
Bat_t bat_init(void) 
{
    Bat_t new_bat;
    new_bat.position = 3;
    return new_bat;
}


/** Display the bat on the led matrix 
    @param the current bat object */
void bat_display(Bat_t bat)
{
    tinygl_point_t start_of_bat;
    tinygl_point_t end_of_bat;
    //Calculating the coord for the start and end of the bat
    start_of_bat = tinygl_point (4, bat.position-1);
    end_of_bat = tinygl_point (4, bat.position + 1);
    tinygl_pixel_value_t led_on = 1;
    //Using tingygl to display the bat
    tinygl_draw_line(start_of_bat, end_of_bat, led_on);
}


/** Checks if the nav switch has been pressed and move the bat position accordingly 
    @param the current bat object 
    @return the new bat object with updated position */
Bat_t bat_update_position(Bat_t bat)
{
    // Increment the position if SOUTH is pressed. (representing the bat moving RIGHT)
    if (navswitch_push_event_p (NAVSWITCH_SOUTH)) {
        //check if the new position will be in the bounds of the screen.
        if (bat.position < 5) {
            bat.position ++;
        }
    }
    //Decrement position if NORTH is pressed. (representing the bat moving LEFT)
    if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
        //Check if the new position will be in the bounds of the screen.
        if (bat.position > 1) {
            bat.position --;
        }        
    }
    navswitch_update();
    return bat;
}