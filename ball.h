/*
    File:    ball.h
    Authors: Jemima Gregory, Jee Park
    Date:    11 October 2022
    Descr:   Functionality of the ball object, its movement and its display
*/

#ifndef BALL_H
#define BALL_H

#include "bat.h"


/** The ball direction enum */
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

/** The ball structure */
typedef struct {
    int8_t x; 
    int8_t y;
    Direction dir;
    bool missed;
    bool display;
} Ball_t;

/** Initialise the ball object - called when the game begins, 
    thus the ball is initiated with the same start position 
    and direction each time.
    @return a new ball object */
Ball_t ball_init(void);

/** Update the direction of the ball
    @param the current ball object
    @param the current bat object
    @return the new ball object with updated direction*/
Ball_t ball_update_direction(Ball_t ball, Bat_t bat);

/** Updates the ball coordinates, depending on it's current direction.
    @param the current ball object 
    @return the new ball object with an updated cordinate*/
Ball_t ball_update_position (Ball_t the_ball);

/** Display the position of the ball
    @param the current ball object to display on board*/
void ball_display(Ball_t the_ball);

#endif