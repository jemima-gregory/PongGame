/*
    File:    game.c
    Authors: Jemima Gregory, Jee Park
    Date:    10 October 2022
    Descr:   The main game file.
*/

#include "system.h"
#include "pacer.h"
#include "comment.h"
#include "stage.h"
#include "led.h"
#include "navswitch.h"
#include "display.h"
#include "tinygl.h"
#include "ir_uart.h"

#define PACER_RATE 500
#define RESTART_UPDATE_COUNTER 100
#define INITIAL_UPDATE_COUNTER 0 
#define LED_OFF 0

int main (void)
{
    // intialize everything
    system_init();
    pacer_init(PACER_RATE);
    comment_init();
    navswitch_init();
    led_init();
    led_set(LED1, LED_OFF);
    display_init();
    ir_uart_init();

    // get the start stage
    game_stage_t stage = stage_start();

    uint8_t update_ball_counter = INITIAL_UPDATE_COUNTER;

    while(1)
    {
        pacer_wait();
        update_ball_counter++;
        // Makes sure that the ball is only updated every few cycles
        if (update_ball_counter > RESTART_UPDATE_COUNTER) {
            update_ball_counter = INITIAL_UPDATE_COUNTER;
        }

        if (stage == START) {
            stage = stage_start();
        } else if (stage == PLAYING) {
            stage = stage_playing(update_ball_counter);
        } else {
            stage = stage_end();
        }
        tinygl_update();
    }
    return 0;
}
