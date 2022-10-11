#include "system.h"
#include "display.h"
#include "navswitch.h"
#include "pacer.h"
#include "bat.h"


//Initiates the bat object - is called when the game begins, so the bat is initiated with the same start position each time, 3, "the middle".
int8_t init_bat(void) 
{
    int8_t bat_position = 3;
    
    return bat_position;
}


//Display the bat on the led matrix
void display_bat(int8_t bat)
{
    //set all pixels to off, before setting the next position
    display_clear();

    switch(bat)
    {
        case 1:
            display_pixel_set(5,7,1);
            display_pixel_set(5,6,1);
            display_pixel_set(5,5,1);
            break;
        case 2:
            display_pixel_set(5,6,1);
            display_pixel_set(5,5,1);
            display_pixel_set(5,4,1);
            break;
        case 3:
            display_pixel_set(5,5,1);
            display_pixel_set(5,4,1);
            display_pixel_set(5,3,1);
            break;    
        case 4:
            display_pixel_set(5,4,1);
            display_pixel_set(5,3,1);
            display_pixel_set(5,2,1);
            break;
        case 5:
            display_pixel_set(5,3,1);
            display_pixel_set(5,2,1);
            display_pixel_set(5,1,1);
            break;
    }
}


void check_navswitch(void)
{
    // Increment the position if NORTH is pressed. (representing the bat moving RIGHT)
    if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
        //check if the new position will be in the bounds of the screen.
        if (bat_position < 5) {
            bat_position ++;
        }
    }
    // Decrement position if SOUTH is pressed. (representing the bat moving LEFT)
    if (navswitch_push_event_p (NAVSWITCH_SOUTH)) {
        //check if the new position will be in the bounds of the screen.
        if (bat_position > 1) {
            bat_position --;
        }        
    }
}