#include "system.h"
#include "pacer.h"
#include "comment.h"
#include "stage.h"
#include "led.h"
#include "navswitch.h"
#include "display.h"
#include "ledmat.h"
#define PACER_RATE 500


int main (void)
{
    system_init();
    pacer_init(PACER_RATE);
    comment_init();
    navswitch_init();
    led_init();
    //display_init();
    //ledmat_init();


    led_set(LED1, 0);

    game_stage_t stage = start_stage();

    while(1)
    {
        pacer_wait();

        if (stage == START) {
            stage = start_stage();
        } else if (stage == PLAYING) {
            stage = playing_stage();
        } else {
            stage = end_stage();
        }

    }
    return 0;
}
