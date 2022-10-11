#ifndef BALL_H
#define BALL_H

#include <stdint.h>


// Direction of the ball
typedef enum {
    DIR_N, 
    DIR_S,
    DIR_E,
    DIR_W,
    DIR_NE,  
    DIR_SE,  
    DIR_NW,
    DIR_SW
} direction;

// Defining the ball object, the position and direction
typedef struct {
    int8_t row; 
    int8_t col;
    direction dir;
} ball;


void display_ball_position(int8_t row, int8_t col);

void check_ball_position(void);

#endif