#include "system.h"
#include "display.h"
#include "pacer.h"



//Initiates the ball object - called when the game begins, thus the ball is initiated with the same start position and direction each time.
Ball ball_init(void)
{
    ball new_ball;
    new_ball.row = 4;
    new_ball.col = 3;
    new_ball.dir = NORTH;

    return new_ball;
}


Ball update_ball_direction(Ball the_ball)
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

    return the_ball;
}


//Updates the balls coordinates by one, depending on it's current direction.
Ball update_ball_position (Ball the_ball)
{
    if (dir == NORTH) {
        col --;
    } else if (dir == SOUTH) {
        col ++;
    } else if (dir == NORTH_EAST) {
        col --;
        row --;
    } else if (dir == NORTH_WEST) {
        col --;
        row ++;       
    } else if (dir == SOUTH_EAST) {
        col ++;
        row --;
    } else {
        //direction is SOUTHWEST
        col ++;
        row ++;
    }

    return the_ball;
}


//Display the position of the ball
void display_ball(Ball the_ball)
{
    //set all pixels to off, before setting the next position of the ball
    display_clear();

    //set the pixel on at the 
    display_pixel_set(col, row, 1);
}