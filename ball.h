/*
    File:    ball.h
    Authors: Jemima Gregory, Jee Park
    Date:    11 October 2022
    Descr:   Functionality of the ball object, its movement and its display
*/

#ifndef BALL_H
#define BALL_H

#include "bat.h"


//Direction of the ball
typedef enum {
    NORTH, 
    NORTH_EAST,
    EAST,
    SOUTH_EAST,
    SOUTH,
    SOUTH_WEST,
    WEST,
    NORTH_WEST
} Direction;

//Defining the ball object, the position and direction
typedef struct {
    int8_t x; 
    int8_t y;
    Direction dir;
    bool missed;
    bool display;
} Ball_t;

//Initialise the ball
Ball_t ball_init(void);

//Update the ball direction
Ball_t ball_update_direction(Ball_t ball, Bat_t bat);

//Update the ball position
Ball_t ball_update_position (Ball_t the_ball);

//Display the ball on the led matrix
void ball_display(Ball_t the_ball);

#endif