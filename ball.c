#include "system.h"
#include "display.h"
#include "pacer.h"
#include "ball.h"
#include "bat.h"


//Initiates the ball object - called when the game begins, thus the ball is initiated with the same start position and direction each time.
Ball_t ball_init(void)
{
    Ball_t new_ball;
    new_ball.row = 4;
    new_ball.col = 3;
    new_ball.dir = SOUTH; // ------------HAVE SET THIS TO SOUTH FOR ****TESTING**** , ONCE THE GAME USES IR, CHANGE IT TO 'NORTH' -------------------------------------------------

    return new_ball;
}


Ball_t update_ball_direction(Ball_t ball, Bat_t bat)
{
    int8_t bat_pos = bat.position;
    int8_t row = ball.row;
    int8_t col = ball.col;
    //Dealing with potential changes of direction first:

    // If the ball 'hits' either wall - row 1 or 7 (right and left to us), then adjust it's direction accordingly
    //row1 (right-hand wall)
    if (row == 1) {
        if (ball.dir == NORTH_EAST) {
            ball.dir = NORTH_WEST;
        } else {
            ball.dir = SOUTH_WEST;
        }

    //row7 (left-hand wall)
    } else if (row == 7) {
        if (ball.dir == NORTH_WEST) {
            ball.dir = NORTH_EAST;
        } else {
            ball.dir = SOUTH_EAST;
        }
    }


    //The ball reached the bottom of the board. (from the player's pov)
    if (col == 5) {
        //The ball hits the centre of the bat
        if (((row == 6) && bat_pos == 1) || ((row == 5) && bat_pos == 2) || ((row == 4) && bat_pos == 3) || ((row == 3) && bat_pos == 4) || ((row == 2) && bat_pos == 5)) {
            ball.dir = NORTH;
        }

        //The ball hits the left side of the bat
        //if the ball hits the edge of the bat, but it's also against the edge - go the opposite way to the wall, diagonally.
        if ((row == 7) && (bat_pos == 1)) {
            ball.dir = NORTH_EAST;
        
        //left edge
        } else if (((row == 6) && (bat_pos == 2)) || ((row == 5) && (bat_pos == 3)) || ((row == 4) && (bat_pos== 4)) || ((row == 3) && (bat_pos == 5))) {
            ball.dir = NORTH_WEST;

        //if the ball hits the edge of the bat, but it's also against the edge - go the opposite way to the wall, diagonally.
        } else if ((row == 1) && (bat_pos == 5)) {
            ball.dir = NORTH_WEST;
        
        //right edge
        } else if (((row == 5) && (bat_pos == 1)) || ((row == 4) && (bat_pos == 2)) || ((row == 3) && (bat_pos== 3)) || ((row == 2) && (bat_pos == 4))) {
            ball.dir = NORTH_EAST;
        }

        //if the ball doesn't hit the bat
        //add win to score or return miss
    }

    return ball;
}


//Updates the balls coordinates by one, depending on it's current direction.
Ball_t update_ball_position (Ball_t the_ball)
{
    if (the_ball.dir == NORTH) {
        the_ball.col --;
    } else if (the_ball.dir == SOUTH) {
        the_ball.col ++;
    } else if (the_ball.dir == NORTH_EAST) {
        the_ball.col --;
        the_ball.row --;
    } else if (the_ball.dir == NORTH_WEST) {
        the_ball.col --;
        the_ball.row ++;       
    } else if (the_ball.dir == SOUTH_EAST) {
        the_ball.col ++;
        the_ball.row --;
    } else {
        //direction is SOUTHWEST
        the_ball.col ++;
        the_ball.row ++;
    }

    return the_ball;
}


//Display the position of the ball
void display_ball(Ball_t the_ball)
{
    //set all pixels to off, before setting the next position of the ball
    display_clear();

    //set the pixel on at the 
    display_pixel_set(the_ball.col, the_ball.row, 1);
}