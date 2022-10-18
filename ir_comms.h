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

void ir_comms_start_game (void);

bool ir_comms_check_start(void);

void ir_comms_outgoing_ball (Ball_t ball);

Ball_t ir_comms_incomming_ball (Ball_t ball, char value);

void ir_comms_ball_missed (void);

void ir_comms_game_end (void);

char ir_comms_playing (void);

#endif