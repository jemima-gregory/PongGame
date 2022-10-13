#include "system.h"
#include "tinygl.h"
#include "pacer.h"
#include "ball.h"
#include "bat.h"
#include "led.h"


// the map the for led matrix (use to calculate coord for tinygl)
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
    return ball;
}


Ball_t update_ball_direction(Ball_t ball, Bat_t bat)
{
    int8_t bat_pos = bat.position;
    //Dealing with potential changes of direction first:

    // If the ball 'hits' either wall - y equal to 0 or 6 (right and left to us), then adjust it's direction accordingly
    //(right-hand wall)
    if (ball.y == 0) {
        if (ball.dir == NORTH_EAST) {
            ball.dir = NORTH_WEST;
        } else {
            ball.dir = SOUTH_WEST;
        }

    //(left-hand wall)
    } else if (ball.y == 6) {
        if (ball.dir == NORTH_WEST) {
            ball.dir = NORTH_EAST;
        } else {
            ball.dir = SOUTH_EAST;
        }
    }

    // -----------------TESTING--------------
    if (ball.x == 0) {
        ball.dir = SOUTH;
    }

    //The ball reached the bottom of the board. (from the player's pov)
    if (ball.x == 4) {
        //The ball hits the centre of the bat
        if (((ball.y == 5) && bat_pos == 1) || ((ball.y == 4 ) && bat_pos == 2) || ((ball.y == 3) && bat_pos == 3) || ((ball.y == 2) && bat_pos == 4) || ((ball.y == 1) && bat_pos == 5)) {
            ball.dir = NORTH;

        //The ball hits the left side of the bat
        //if the ball hits the edge of the bat, but it's also against the edge - go the opposite way to the wall, diagonally.
        } else if ((ball.y == 6) && (bat_pos == 1)) {
            ball.dir = NORTH_EAST;
        
        //left edge
        } else if (((ball.y == 5) && (bat_pos == 2)) || ((ball.y == 4) && (bat_pos == 3)) || ((ball.y == 3) && (bat_pos== 4)) || ((ball.y == 2) && (bat_pos == 5))) {
            ball.dir = NORTH_WEST;

        //if the ball hits the edge of the bat, but it's also against the edge - go the opposite way to the wall, diagonally.
        } else if ((ball.y == 0) && (bat_pos == 5)) {
            ball.dir = NORTH_WEST;
        
        //right edge
        } else if (((ball.y == 4) && (bat_pos == 1)) || ((ball.y == 3) && (bat_pos == 2)) || ((ball.y == 2) && (bat_pos== 3)) || ((ball.y == 1) && (bat_pos == 4))) {
            ball.dir = NORTH_EAST;
        }

        //if the ball doesn't hit the bat
        //add win to score or return miss
    }

    if (ball.x == 0) {
        ball.dir = SOUTH;
    } 

    return ball;
}


//Updates the balls coordinates by one, depending on it's current direction.
Ball_t update_ball_position (Ball_t the_ball)
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
        //direction is SOUTHWEST
        the_ball.x ++;
        the_ball.y ++;
    }

    return the_ball;
}


//Display the position of the ball
void display_ball(Ball_t ball)
{
    // tinygl_pixel_value_t led_on = 1;
    // tinygl_pixel_set(tinygl_point(ball.x, ball.y), led_on);

    tinygl_point_t start_of_ball;
    tinygl_point_t end_of_ball;

    // calculating the coord for the start and end of the bat
    start_of_ball = tinygl_point(ball.x, ball.y);
    end_of_ball = tinygl_point(ball.x, ball.y);
    
    
    tinygl_pixel_value_t led_on = 1;
    // using tingygl to display the bat
    tinygl_draw_line(start_of_ball, end_of_ball, led_on);
}
