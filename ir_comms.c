#include "system.h"
#include "ir_uart.h"




//Working from the lab3.3 file

void ir_comms (void) 
{

}

// Encodes the ball's values (x,y,direction) in a 
void ir_comms_outgoing_ball (Ball_t ball) 
{

    // encoded_val is a char value which encodes the x,y coords and direction.
    char encoded_val = ...

    ir_uart_putc(encoded_val);
}


// Decodes the info recieved by the ir, returns the ball's value
Ball_t ir_comms_incomming_ball (void) 
{
    char value = ir_uart_getc();

    //value needs to be decoded from a char value to the x,y and direction values.
}