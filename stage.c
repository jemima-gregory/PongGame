/*
    File:    stage.c
    Authors: Jee Park, Jemima Gregory
    Date:    11 October 2022
    Descr:   Contains the game logic and functionality for each of the stages of play
*/

#include "system.h"
#include "navswitch.h"
#include "ir_uart.h"
#include "tinygl.h"
#include "ir_comms.h"

#include "stage.h"
#include "comment.h"
#include "bat.h"
#include "ball.h"
#include "led.h"

#define SCORE_0 48
#define SCORE_3 51
#define OFF_BOARD -1
#define MISSED 'm'
#define GAME_END 'e'
#define START_SCORE_COUNTER 0
#define END_SCORE_COUNTER 1300
#define UPDATE_BALL 99
#define START_ENCODED_BALL 0
#define END_ENCODED_BALL 80
#define LED_OFF 0
#define LED_ON 1

// To check if its the first time entering the start stage
static bool first_start_stage = true;
// To check if its the first time entering the end stage
static bool first_end_stage = true;
//A counter to count how long the score is to be displayed
static int16_t display_score_counter = 0;
//Creating a ball object
static Bat_t bat;
//Creating a ball object
static Ball_t ball;
//Score1 is this players score and is set to 0
static char score = SCORE_0;
//Bool to decide when the score is displayed
static bool display_score = false;


/** The start stage of the game 
    @return the next stage */
game_stage_t stage_start(void)
{
    //If this is the first time the function is being called, display the intro comment
    if (first_start_stage) {
        tinygl_clear();
        comment_intro();
        first_start_stage = false;
        led_set(LED1, LED_ON);
    }

    //If the nav switch is pushed, change to the playing stage
    if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
        led_set(LED1, LED_OFF);
        //Send the start signal to the other player
        ir_comms_start_game();
        //Seting the ball to display on this players board
        ball.display = true;

        first_start_stage = true;
        bat = bat_init();
        ball = ball_init();
        tinygl_clear();
        return PLAYING;
    }

    //Checking to see if start signal has been sent by other player
    if (ir_comms_check_start()) {
        led_set(LED1, LED_OFF);
        first_start_stage = true;
        bat = bat_init();
        ball = ball_init();
        tinygl_clear();
        ball.display = false;
        return PLAYING;
    }
    

    navswitch_update();
    return START;
}

/** The playing stage is where the actual game is displayed and managed 
    @return the next stage */
game_stage_t stage_playing(int8_t update_ball_counter)
{
    char value = ir_comms_playing();
    if (value == GAME_END) {
        return END;
    }

    if (value == MISSED) {
        score++;
        display_score = true;
    } 

    if (display_score) {  

        if (display_score_counter == START_SCORE_COUNTER) {
            tinygl_clear();
            //Display the players score
            comment_score(score);
            //Increment the score counter
            display_score_counter++;
        }

        //Increment the score counter
        display_score_counter++;

        // stop displaying the score
        if (display_score_counter > END_SCORE_COUNTER) {
            display_score = false;
            display_score_counter = 0;
            bat.position = 3;
            ball.missed = false;
            ball.x = 0;
            ball.y = 3;
            ball.dir = SOUTH;
            
            /* The game has finished since one 
            of the players have scored 3 points */
            if (score == SCORE_3) {
                ir_comms_game_end();
                return END;
            } else if (value == GAME_END) {
                return END;
            }
        }

    } else { 
        
        // If value represents the encoded ball value then update ball
        if (value >= START_ENCODED_BALL && value <= END_ENCODED_BALL) {
            ball = ir_comms_incomming_ball(ball, value);
            ball.x ++;
            ball.display = true;
        }

        tinygl_clear();
        //Display bat
        bat_display(bat);
        //Update the bat positoin
        bat = bat_update_position(bat);
        
        //Display ball
        if (ball.display) {
            ball_display(ball);
            //Every 50th time it enters this call, update ball positon
            if (update_ball_counter > UPDATE_BALL) {
                ball = ball_update_position(ball);
                ball = ball_update_direction(ball, bat);
            }
            if (ball.missed) {
                display_score = true;
                ir_comms_ball_missed();
            }
            //The ball has reached the top of the board. (from the player's pov) It goes to the other player
            if (ball.x == OFF_BOARD) {
                ir_comms_outgoing_ball(ball);
                ball.display = false;
            }
        }
    }
    
    return PLAYING;
}

/** The end stage of the game 
    @return the next stage */
game_stage_t stage_end(void)
{
    //If this is the first time the function is being called, display the end comment
    if (first_end_stage) {
        comment_end();
        first_end_stage = false;
        led_set(LED1, LED_ON);
    }

    //If the nav switch is pushed, change to the start stage
    if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
        led_set(LED1, LED_OFF);
        first_end_stage = true;
        score = SCORE_0;
        navswitch_update();
        ir_comms_restart_game();
        return START;
    }

    //Checking to see if restart signal has been sent by other player
    if (ir_comms_check_restart()) {
        led_set(LED1, LED_OFF);
        first_end_stage = true;
        score = SCORE_0;
        navswitch_update();
        return START;
    }

    navswitch_update();
    return END;
}