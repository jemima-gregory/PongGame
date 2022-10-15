/*
    File:    ir_comms.c
    Authors: Jemima Gregory, Jee Park
    Date:    13 October 2022
    Descr:   Contains the functionality for the ir communication between the two players
*/

#ifndef IR_COMMS_H
#define IRS_COMMS_H

void ir_comms_init (void);

void ir_comms_outgoing_ball (Ball_t ball);

Ball_t ir_comms_incomming_ball (void);

#endif