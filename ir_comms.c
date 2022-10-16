/*
    File:    ir_comms.c
    Authors: Jemima Gregory, Jee Park
    Date:    13 October 2022
    Descr:   Contains the functionality for the ir communication between the two players
*/

#include "system.h"
#include "ir_uart.h"

//Offset is 8 as there are 8 values for direction
#define XCOORD_OFFSET 8


//Working from the lab3.3 file

void ir_comms (void) 
{

}

//Encodes the ball's values (x,y,direction) in a 
void ir_comms_outgoing_ball (Ball_t ball) 
{
    //Encoded_val is a char value which encodes the x coord (multiplied by the offset so each combination of x and dir are distinct) and direction.
    char encoded_val = ball.x * XCOORD_OFFSET + ball.dir;

    ir_uart_putc(encoded_val);
}


//Decodes the info recieved by the ir, returns the ball's value
Ball_t ir_comms_incomming_ball (Ball_t ball) 
{
    char value = ir_uart_getc();

    //Value is decoded from a char value to get the direction
    ball.dir = value % XCOORD_OFFSET;

    //Value is decoded from a char value to get the x-coord
    ball.x = (value - ball.dir) / XCOORD_OFFSET;
}