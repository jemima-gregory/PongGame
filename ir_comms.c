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
#define SCORE_0 48
#define MISSED 'm'
#define GAME_END 'e'
#define OFF_BOARD -1

//Start val is the value which conveys that the game should start
//#define START_VAL 

//Sends the start signal to the other player
void ir_comms_start_game (void) 
{
    ir_uart_putc(START);
}

//
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
Ball_t ir_comms_incomming_ball (Ball_t ball, char value) 
{
    //Value is decoded from a char value to get the direction
    int8_t y_cord = value % 10;
    ball.y = 6 - y_cord;

    //Value is decoded from a char value to get the x-coord
    ball.dir = (((value - y_cord) / 10) + 4) % 8;
    return ball;
}

//
void ir_comms_ball_missed (void) {
    ir_uart_putc(MISSED);
}

void ir_comms_game_end (void) {
    ir_uart_putc(GAME_END);
}

char ir_comms_playing (void) {
    if (ir_uart_read_ready_p()) {
        char c = ir_uart_getc();
        // To reduce IR interference
        if (c >= 0 && c <= 110) {
            return c;
        }
    }
    return 111;
}