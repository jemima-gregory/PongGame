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
} Ball_t;

Ball_t ball_init(void);

Ball_t update_ball_direction(Ball_t ball, Bat_t bat);

Ball_t update_ball_position (Ball_t the_ball);

void display_ball(Ball_t the_ball);

#endif