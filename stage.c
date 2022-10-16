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

//A count that counts the the number of comments displayed. There is always 4 comments displayed each game.
static int comment_count = 0;
//A counter to count how long the score is to be displayed
static int16_t comment_score_count = 1;
//This is to control whether the ball or bat is to be displayed 
bool display_state = true;
//Creating a ball object
static Bat_t bat;
//Creating a ball object
static Ball_t ball;
//Score1 is this players score and is set to 0
static char score1 = 48;
//Score 2 is the opponents score and is set to 0
static char score2 = 48;

//The start stage of the game
game_stage_t stage_start(void)
{
    //If this is the first time the function is being called, display the intro comment
    if (comment_count == 0) {
        tinygl_clear();
        comment_intro();
        comment_count++;
    }

    //If the nav switch is pushed, change to the playing stage
    if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
        bat = bat_init();
        ball = ball_init();
        tinygl_clear();
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
        if (comment_count == comment_score_count) {
            tinygl_clear();
            score2 ++;
            //Display the score
            comment_score(score1, score2);
            comment_count++;
            //Increment the score counter
            comment_score_count++;
        }
        //Increment the score counter
        comment_score_count++;
        /* If the score counter reaches 1300 that means the score has finished being
        displayed. The ball and bat is set back to initial settings and the game
        is played again */
        if (comment_score_count > 1300) {
            if (score1 == 51 || score2 == 51) {
                return END;
            }
            ball.missed = false;
            comment_score_count = comment_count;
            ball.x = 0;
            ball.y = 3;
            ball.dir = SOUTH;
            bat.position = 3;
        }

    } else {
        
        //Checking if there is incoming ir to be read, and updating the position of the ball if this is the case
        if (ir_ur_read_ready_p()) {
            ball = ir_comms_incomming_ball(ball);
            //Ball starts displaying as it 'enters' the player's board ---------------------------------------------------------- NEEDS TO BE IMPLEMENTED ---------------

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
            //Every 50th time it enters this call, update ball positon
            if (update_ball > 49) {
                ball = ball_update_position(ball);
                ball = ball_update_direction(ball, bat);
            }
            ball_display(ball);
            display_state = true;
        }
    }
    
    return PLAYING;
}

//The end stage of the game
game_stage_t stage_end(void)
{
    //If this is the first time the function is being called, display the end comment
    if (comment_count == 4) {
        comment_end();
        comment_count++;
    }

    //If the nav switch is pushed, change to the start stage
    if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
        comment_count = 0;
        comment_score_count = 1;
        score1 = 48;
        score2 = 48;
        navswitch_update();
        return START;
    }

    navswitch_update();
    return END;
}