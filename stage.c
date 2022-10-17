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

#include "stage.h"
#include "comment.h"
#include "bat.h"
#include "ball.h"
#include "led.h"

#define SCORE_0 48

// To check if its the first time entering the start stage.
static bool first_start_stage = true;
// To check if its the first time entering the end stage.
static bool first_end_stage = true;
//A counter to count how long the score is to be displayed
static int16_t comment_score_count = 0;
//This is to control whether the ball or bat is to be displayed 
bool display_state = true;
//Creating a ball object
static Bat_t bat;
//Creating a ball object
static Ball_t ball;
//Score1 is this players score and is set to 0
static char score = SCORE_0;

//The start stage of the game
game_stage_t stage_start(uint64_t start_counter)
{
    //If this is the first time the function is being called, display the intro comment
    if (first_start_stage) {
        tinygl_clear();
        comment_intro();
        first_start_stage = false;
    }

    //If the nav switch is pushed, change to the playing stage
    if (navswitch_push_event_p(NAVSWITCH_PUSH)) {

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
    if (ir_ur_read_ready_p()) {
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

//The playing stage is where the actual game is displayed and managed
game_stage_t stage_playing(int8_t update_ball)
{

    //If the ball is missed then the opponents score goes up 1 and the score is displayed
    if (ball.missed) {
        if (comment_score_counter = 0) {
            tinygl_clear();
            //Display the score
            comment_score(score);
            //Increment the score counter
            comment_score_counter++;
        }
        //Increment the score counter
        comment_score_counter++;
        /* If the score counter reaches 1300 that means the score has finished being
        displayed. The ball and bat is set back to initial settings and the game
        is played again */
        if (comment_score_counter > 1300) {
            if (score == 51) {
                return END;
            }
            ball.missed = false;
            comment_score_counter = 0;
            ball.x = 0;
            ball.y = 3;
            ball.dir = SOUTH;
            bat.position = 3;
        }

    } else {
        
        //Checking if there is incoming ir to be read, and updating the position of the ball if this is the case
        if (ir_ur_read_ready_p()) {
            ball = ir_comms_incomming_ball(ball);
            ball.display = true;
        }


        tinygl_clear();
        //Display bat
        if (display_state == true) {
            bat_display(bat);
            //Update the bat positoin
            bat = bat_update_position(bat);
            display_state = false;
        //Display ball
        } else {
            //If ball is on this players screen
            if (ball.display) {
                //Every 50th time it enters this call, update ball positon
                if (update_ball > 49) {
                    ball = ball_update_position(ball);
                    ball = ball_update_direction(ball, bat);
                }
                
                //The ball has reached the top of the board. (from the player's pov) It goes to the other player
                if (ball.x == -1) {
                    ir_comms_outgoing_ball(ball);
                    ball.display = false;
                }
                ball_display(ball);
                display_state = true;
            }
        }
    }
    
    return PLAYING;
}

//The end stage of the game
game_stage_t stage_end(void)
{
    //If this is the first time the function is being called, display the end comment
    if (first_end_stage) {
        comment_end();
        first_end_stage = false;
    }

    //If the nav switch is pushed, change to the start stage
    if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
        first_end_stage = true;
        score = SCORE_0;
        navswitch_update();
        return START;
    }

    navswitch_update();
    return END;
}