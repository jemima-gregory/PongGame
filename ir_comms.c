/*
    File:    ir_comms.c
    Authors: Jemima Gregory, Jee Park
    Date:    13 October 2022
    Descr:   Contains the functionality for the ir communication between the two players
*/

#include "system.h"
#include "ir_uart.h"
#include "ir_comms.h"

// start signal variable
#define START 's'
// end of game signal variable 
#define GAME_END 'e'
// restart game signal variable
#define RESTART 'r'
// ball was missed signal variable
#define MISSED 'm'
// the char '0' in ascii 
#define SCORE_0 48
// the ball is off the matrix board
#define OFF_BOARD -1
// If nothing has been recieved by the IR
#define NOTHING_RECIEVED 111


/** Sends the start signal to the other player */
void ir_comms_start_game (void) 
{
    ir_uart_putc(START);
}

/** Checks if the start signal has been recieved 
    @return true if start signal recieved else false */
bool ir_comms_check_start(void) 
{
    if (ir_uart_read_ready_p()) {
        char c = ir_uart_getc();
        // To reduce IR interference
        if (c == START) {
            return true;
        }
    }
    return false;
}

/** Sends the restart game signal to the other player */
void ir_comms_restart_game (void) 
{
    ir_uart_putc(RESTART);
}

/** Checks if the restart signal has been recieved 
    @return true if restart signal recieved else false */
bool ir_comms_check_restart(void) 
{
    if (ir_uart_read_ready_p()) {
        char c = ir_uart_getc();
        // To reduce IR interference
        if (c == RESTART) {
            return true;
        }
    }
    return false;
}

/** Checks if any IR communication for the playing stage has been recieved 
    @return value from the ir if valid else return NOTHING_RECIEVED */
char ir_comms_playing (void) 
{
    if (ir_uart_read_ready_p()) {
        char c = ir_uart_getc();
        // To reduce IR interference
        if (c >= 0 && c <= 110) {
            return c;
        }
    }
    return NOTHING_RECIEVED;
}

/** Encodes the ball's values (x,y,direction) in a variable and sends it to the other player
    @param the ball object that you want to send to the other board */
void ir_comms_outgoing_ball (Ball_t ball) 
{
    // The ball direction is in the tens column and the ball y position is in the ones column.
    char encoded_val = (ball.dir * 10) + ball.y;
    ir_uart_putc(encoded_val);
}


/** Decodes the ball information from value 
    @param the current ball object
    @param the encoded ball value recieved that is to be decoded */
Ball_t ir_comms_incomming_ball (Ball_t ball, char value) 
{
    //Value is decoded to get the y cord
    int8_t y_cord = value % 10;
    ball.y = 6 - y_cord;

    //Value is decoded to get the direction
    ball.dir = (((value - y_cord) / 10) + 4) % 8;
    return ball;
}

/** Send signal to the other player that they have scored */
void ir_comms_ball_missed (void) 
{
    ir_uart_putc(MISSED);
}

/** Sends signal to the other player that the game has ended */
void ir_comms_game_end (void) 
{
    ir_uart_putc(GAME_END);
}
