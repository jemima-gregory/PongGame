#ifndef IR_COMMS_H
#define IRS_COMMS_H

void ir_comms_init (void);

void ir_comms_outgoing_ball (Ball_t ball);

Ball_t ir_comms_incomming_ball (void);

#endif