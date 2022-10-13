#include "system.h"
#include "pacer.h"
#include "comment.h"
#include "stage.h"
#include "led.h"
#include "navswitch.h"
#include "display.h"
#include "tinygl.h"

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

    game_stage_t stage = start_stage();

    uint8_t count = 0;

    while(1)
    {
        pacer_wait();
        count++;
        if (count > 50) {
            count = 0;
        }
        if (stage == START) {
            stage = start_stage();
        } else if (stage == PLAYING) {
            tinygl_clear();
            stage = playing_stage(count);
        } else {
            stage = end_stage();
        }
        tinygl_update();
    }
    return 0;
}
