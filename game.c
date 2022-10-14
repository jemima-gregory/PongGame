#include "system.h"
#include "pacer.h"
#include "comment.h"
#include "stage.h"
#include "led.h"
#include "navswitch.h"
#include "display.h"
#include "tinygl.h"
//#include "ir_uart.h"

#define PACER_RATE 500


int main (void)
{
    system_init();
    pacer_init(PACER_RATE);
    comment_init();
    navswitch_init();
    led_init();
    led_set(LED1, 0);
    display_init();
    //ir_uart_init();


    game_stage_t stage = stage_start();

    uint8_t update_ball = 0;

    while(1)
    {
        pacer_wait();
        update_ball++;
        if (update_ball > 50) {
            update_ball = 0;
        }
        if (stage == START) {
            stage = stage_start();
        } else if (stage == PLAYING) {
            stage = stage_playing(update_ball);
        } else {
            stage = stage_end();
        }
        tinygl_update();
    }
    return 0;
}
