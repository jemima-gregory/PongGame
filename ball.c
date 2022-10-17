/*
    File:    ball.c
    Authors: Jemima Gregory, Jee Park
    Date:    11 October 2022
    Descr:   Functionality of the ball object, its movement and its display
*/

#include "system.h"
#include "tinygl.h"
#include "pacer.h"
#include "ball.h"
#include "bat.h"
#include "led.h"


//The map the for led matrix (use to calculate coord for tinygl)
// ------y------
// 6 5 4 3 2 1 0
// o o o o o o o 0  |
// o o o o o o o 1  |
// o o o o o o o 2  x
// o o o o o o o 3  |
// o o o o o o o 4  |

//Initiates the ball object - called when the game begins, thus the ball is initiated with the same start position and direction each time.
Ball_t ball_init(void)
{
    Ball_t ball;
    ball.x = 0;
    ball.y = 3;
    ball.dir = SOUTH;
    ball.missed = false;
    ball.display = true;
    return ball;
}

//Update the direction of the ball
Ball_t ball_update_direction(Ball_t ball, Bat_t bat)
{
    int8_t bat_pos = bat.position;

    //If the ball 'hits' either wall - y equal to 0 or 6 (right and left to us), then adjust it's direction accordingly
    if (ball.dir != SOUTH && ball.dir != NORTH) {
        // The ball hits the right wall
        if (ball.y == 0) {
            if (ball.dir == NORTH_EAST) {
                ball.dir = NORTH_WEST;
            } else {
                ball.dir = SOUTH_WEST;
            }

        //The ball htis the left wall
        } else if (ball.y == 6) {
            if (ball.dir == NORTH_WEST) {
                ball.dir = NORTH_EAST;
            } else {
                ball.dir = SOUTH_EAST;
            }
        }
    }

    //The ball reached the bottom of the board. (from the player's pov)
    if (ball.x == 4) {
        //Ball hits the centre of the bat
        if (ball.y == bat_pos) {
            ball.dir = NORTH;

        //Ball hits the left edge of the bat, but the bat is also against the edge of the board
        } else if ((ball.y == 6) && (bat_pos == 5)) {
            ball.dir = NORTH_EAST; 
        
        //Ball hits the left edge of the bat
        } else if (ball.y == bat_pos + 1) {
            ball.dir = NORTH_WEST;

        //Ball hits the right edge of the bat, but the bat is also against the edge of the board
        } else if ((ball.y == 0) && (bat_pos == 1)) {
            ball.dir = NORTH_WEST;
        
        //Ball hits the right edge of the bat
        } else if (ball.y == bat_pos - 1) {
            ball.dir = NORTH_EAST;
    
        //Ball doesn't hit the bat
        } else {
            ball.missed = true;
        }

    }

    return ball;
}


//Updates the ball coordinates by one, depending on it's current direction.
Ball_t ball_update_position (Ball_t the_ball)
{
    if (the_ball.dir == NORTH) {
        the_ball.x --;
    } else if (the_ball.dir == SOUTH) {
        the_ball.x ++;
    } else if (the_ball.dir == NORTH_EAST) {
        the_ball.x --;
        the_ball.y --;
    } else if (the_ball.dir == NORTH_WEST) {
        the_ball.x --;
        the_ball.y ++;       
    } else if (the_ball.dir == SOUTH_EAST) {
        the_ball.x ++;
        the_ball.y --;
    } else if (the_ball.dir == SOUTH_WEST) {
        the_ball.x ++;
        the_ball.y ++;
    }

    return the_ball;
}


//Display the position of the ball
void ball_display(Ball_t ball)
{
    tinygl_pixel_value_t led_on = 1;
    //Using tingygl to display the ball
    tinygl_draw_point(tinygl_point(ball.x, ball.y), led_on);
}
