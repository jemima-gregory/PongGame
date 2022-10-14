#ifndef BALL_H
#define BALL_H

#include <stdint.h>
#include "bat.h"


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
    int8_t x; 
    int8_t y;
    Direction dir;
    bool missed;
} Ball_t;

// initialize the ball
Ball_t ball_init(void);

// Update the ball direction
Ball_t ball_update_direction(Ball_t ball, Bat_t bat);

// Update the ball position
Ball_t ball_update_position (Ball_t the_ball);

// Display the ball on the matrix
void ball_display(Ball_t the_ball);

#endif