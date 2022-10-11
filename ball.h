#ifndef BALL_H
#define BALL_H

#include <stdint.h>


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
} Direction;

// Defining the ball object, the position and direction
typedef struct {
    int8_t row; 
    int8_t col;
    Direction dir;
} Ball;

Ball ball_init(void);

Ball update_ball_direction(Ball the_ball);

Ball update_ball_position (Ball the_ball);

void display_ball(Ball the_ball);

#endif