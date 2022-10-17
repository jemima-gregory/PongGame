/*
    File:    ir_comms.c
    Authors: Jemima Gregory, Jee Park
    Date:    13 October 2022
    Descr:   Contains the functionality for the ir communication between the two players
*/

#include "system.h"
#include "ir_uart.h"
#include "ir_comms.h"
//Offset is 8 as there are 8 values for direction
#define XCOORD_OFFSET 8
#define START 's'

//Start val is the value which conveys that the game should start
//#define START_VAL 

//Sends the start signal to the other player
void ir_comms_start_game (void) 
{
    ir_uart_putc(START);
}

bool ir_comms_check_start(void) {
    if (ir_uart_read_ready_p()) {
        char c = ir_uart_getc();
        // To reduce IR interference
        if (c == START) {
            return true;
        }
    }
    return false;
}

//Encodes the ball's values (x,y,direction) in a 
void ir_comms_outgoing_ball (Ball_t ball) 
{
    //Encoded_val is a char value which encodes the x coord (multiplied by the offset so each combination of x and dir are distinct) and direction.
    char encoded_val = (ball.dir * 10) + ball.y;

    ir_uart_putc(encoded_val);
}


//Decodes the info recieved by the ir, returns the ball's value
Ball_t ir_comms_incomming_ball (Ball_t ball) 
{
    char value = ir_uart_getc();

    //Value is decoded from a char value to get the direction
    int8_t y_cord = value % 10;
    ball.y = 6 - y_cord;

    //Value is decoded from a char value to get the x-coord
    ball.dir = (((value - y_cord) / 10) + 4) % 8;

    return ball;
}

//
void ir_comms_send_score (char their_score) {
    ir_uart_putc(their_score);
}

//
char ir_comms_get_score (char my_score) {
    my_score = ir_uart_getc();
    return my_score;
}