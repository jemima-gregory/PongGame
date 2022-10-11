#include "system.h"
#include "navswitch.h"
#include "ir_uart.h"
#include "tinygl.h"

#include "stage.h"
#include "comment.h"
#include "bat.h"
#include "ball.h"

static int comment_count = 0;



game_stage_t start_stage(void)
{
    /*if this is the first time the function is being called*/
    if (comment_count == 0) {
        intro_com();
        comment_count++;
    }

    /* if the nav switch is pushed change to the playing stage*/
    if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
        return PLAYING;
    }

    tinygl_update();
    return START;
}

game_stage_t playing_stage(void)
{
    /* if this is the first time the function is being called */
    Ball_t ball;
    Bat_t bat;
    if (comment_count == 1) {
        //initiating the ball and the bat
        ball = ball_init();
        bat = init_bat();
    }

    //checking the nav switch for actions performed
    bat = check_navswitch(bat);
    //checking if the ball has 'hit' anything
    ball = update_ball_direction(ball, bat);


    //displaying the bat, in it's current position, on the led matrix
    display_bat(bat);
    //displaying the ball, in it's current position, on the led matrix
    display_ball(ball);


    //moving the ball's position on the led matrix by one
    ball = update_ball_position(ball);


    return PLAYING;
}

game_stage_t end_stage(void)
{
    if (comment_count == 4) {
        end_com();
        comment_count++;
    }

    if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
        comment_count = 0;
        return START;
    }
    return END;
}