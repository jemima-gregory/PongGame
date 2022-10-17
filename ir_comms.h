/*
    File:    ir_comms.c
    Authors: Jemima Gregory, Jee Park
    Date:    13 October 2022
    Descr:   Contains the functionality for the ir communication between the two players
*/

#ifndef IR_COMMS_H
#define IR_COMMS_H

#include "ball.h"

void ir_comms_start_game (void);

void ir_comms_outgoing_ball (Ball_t ball);

Ball_t ir_comms_incomming_ball (Ball_t ball);

#endif