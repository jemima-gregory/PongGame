#include "system.h"
#include "tinygl.h"
#include "ir_uart.h"

/* Need to add these to Makefile:
#include "system.h"
#include "ir_uart.h"
#include "usart1.h"
#include "timer0.h"
#include "pio.h"
#include "delay.h"
*/





//Working from the lab3.3 file


// Encodes the ball's values (x,y,direction) in a 
void outgoing_ball (Ball_t) {

    // encoded_val is a char value which encodes the x,y coords and direction.
    char encoded_val = ...

    ir_uart_putc(encoded_val);
}


// Decodes the info recieved by the ir, returns the ball's value
Ball_t incomming_ball (void) {
    char value = ir_uart_getc();

    //value needs to be decoded from a char value to the x,y and direction values.
}