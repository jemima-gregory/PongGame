#include "system.h"
#include "pacer.h"
#include "comment.h"
#include "stage.h"

#define PACER_RATE 500


int main (void)
{
    game_stage_t stage = gamestart();
    system_init();
    pacer_init(PACER_RATE);
    comment_init();

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
