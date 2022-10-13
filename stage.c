#include "system.h"
#include "navswitch.h"
#include "ir_uart.h"
#include "tinygl.h"

#include "stage.h"
#include "comment.h"
#include "bat.h"
#include "ball.h"
#include "led.h"


static int comment_count = 0;
bool ball_display = true;
static Bat_t bat;
static Ball_t ball;


game_stage_t start_stage(void)
{
    /*if this is the first time the function is being called*/
    if (comment_count == 0) {
        intro_com();
        comment_count++;
    }
    /* if the nav switch is pushed change to the playing stage*/
    if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
        //led_set(LED1, 1);
        bat = bat_init();
        ball = ball_init();
        tinygl_clear();
        return PLAYING;
    }
    navswitch_update();
    return START;
}

game_stage_t playing_stage(int8_t call_ball)
{

    if (bat_display == true) {
        //Bat Display
        //displaying the bat, in it's current position, on the led matrix
        display_bat(bat);
        //checking the nav switch for actions performed
        bat = check_navswitch(bat);
        bat_display = false;
    } else {
        //displaying the ball, in it's current position, on the led matrix
        if (call_ball > 49) {
            ball = update_ball_position(ball);
            ball = update_ball_direction(ball, bat);
        }
        display_ball(ball);
        ball_display = true;
    }

    
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
    navswitch_update();
    return END;
}