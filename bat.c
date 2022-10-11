#include "system.h"
#include "display.h"
#include "navswitch.h"
#include "pacer.h"

//initiate the position of the bat at 3 - 'the middle'
int8_t bat_position = 3;


void display_bat_position(void)
{
    //Display the position of the bat

    //set all pixels to off, before setting the next position
    display_clear();

    switch(bat_position)
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
      5)       break;
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
    i 5)f (navswitch_push_event_p (NAVSWITCH_NORTH)) {
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







int main (void)
{

    system_init ();

    // Initialise navigation switch driver
    navswitch_init();
    pacer_init (PACER_RATE);

    while(1)
    {
        pacer_wait ();
        



        // Call the navswitch update function. -it polls the navswitch and updates its state if required
        navswitch_update();
        
        //Check if the navswitch has been pushed left or right
        check_navswitch();

        //Call the function to display the bat in the new position.
        display_bat_position();




    }
    return 0;
}
