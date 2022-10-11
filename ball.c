#include "system.h"
#include "display.h"
#include "pacer.h"

// Direction of the ball
typedef enum {
    NORTH, 
    SOUTH,
    EAST,
    WEST,
    NORTH_EAST,  
    SOUTH_EAST,  
    NORTH_WEST,
    SOUTH_WEST
} direction;

// Defining the ball object, the position and direction
typedef struct {
    int8_t row; 
    int8_t col;
    direction dir;
} ball;


void check_ball_position(ball ball_object)
{

    //Dealing with potential changes of direction first:

    // If the ball 'hits' either wall - row 1 or 7 (right and left to us), then adjust it's direction accordingly
    //row1 (right-hand wall)
    if (row == 1) {
        if (dir == NORTH_EAST) {
            dir = NORTH_WEST;
        } else {
            dir = SOUTH_WEST;
        }

    //row7 (left-hand wall)
    } else if (row == 7) {
        if (dir == NORTH_WEST) {
            dir = NORTH_EAST;
        } else {
            dir = SOUTH_EAST;
        }
    }


    //The ball reached the bottom of the board. (from the player's pov)
    if (col == 5) {
        //The ball hits the centre of the bat
        if (((row == 6) && bat_position == 1) || ((row == 5) && bat_position == 2) || ((row == 4) && bat_position == 3) || ((row == 3) && bat_position == 4) || ((row == 2) && bat_position == 5)) {
            dir = NORTH;
        }

        //The ball hits the left side of the bat
        //if the ball hits the edge of the bat, but it's also against the edge - go the opposite way to the wall, diagonally.
        if ((row == 7) AND (bat_position == 1)) {
            dir = NORTH_EAST;
        
        //left edge
        } else if (((row == 6) && (bat_position == 2)) || ((row == 5) && (bat_position == 3)) || ((row == 4) && (bat_position == 4)) || ((row == 3) && (bat_position == 5))) {
            dir = NORTH_WEST;

        //if the ball hits the edge of the bat, but it's also against the edge - go the opposite way to the wall, diagonally.
        } else if ((row == 1) AND (bat_position == 5)) {
            dir = NORTH_WEST;
        
        //right edge
        } else if (((row == 5) && (bat_position == 1)) || ((row == 4) && (bat_position == 2)) || ((row == 3) && (bat_position == 3)) || ((row == 2) && (bat_position == 4))) {
            dir = NORTH_EAST;
        }

        //if the ball doesn't hit the bat
        //add win to score or return miss
    }

}










//Display the position of the ball
void display_ball_position(ball ball_object)
{
    //set all pixels to off, before setting the next position of the ball
    display_clear();

    //set the pixel on at the 
    display_pixel_set(ball_object.col, ball_object.row, 1)
}













int main (void)
{

    system_init ();
    pacer_init (PACER_RATE);

    while(1)
    {
        pacer_wait ();
        
        //Call the function to check the current position fo the ball.
        check_ball_position();

        //Call the function to display the bat in it's position.
        display_ball_position(ball_1);

    }
    return 0;
}
