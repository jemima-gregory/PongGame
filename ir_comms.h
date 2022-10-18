/*
    File:    ir_comms.c
    Authors: Jemima Gregory, Jee Park
    Date:    13 October 2022
    Descr:   Contains the functionality for the ir communication between the two players
*/

#ifndef IR_COMMS_H
#define IR_COMMS_H

#include "ball.h"
#include "stdbool.h"

/** Sends the start signal to the other player */
void ir_comms_start_game (void);

/** Checks if the start signal has been recieved 
    @return true if start signal recieved else false */
bool ir_comms_check_start(void);

/** Sends the restart game signal to the other player */
void ir_comms_restart_game (void);

/** Checks if the restart signal has been recieved 
    @return true if restart signal recieved else false */
bool ir_comms_check_restart(void);

/** Checks if any IR communication for the playing stage has been recieved 
    @return value from the ir if valid else return NOTHING_RECIEVED */
char ir_comms_playing (void);

/** Encodes the ball's values (x,y,direction) in a variable and sends it to the other player
    @param the ball object that you want to send to the other board */
void ir_comms_outgoing_ball (Ball_t ball);

/** Decodes the ball information from value 
    @param the current ball object
    @param the encoded ball value recieved that is to be decoded */
Ball_t ir_comms_incomming_ball (Ball_t ball, char value);

/** Send signal to the other player that they have scored */
void ir_comms_ball_missed (void);

/** Sends signal to the other player that the game has ended */
void ir_comms_game_end (void);

#endif