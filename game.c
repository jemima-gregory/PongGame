#include "system.h"
#include "pacer.h"
#include "comment.h"

#define PACER_RATE 500

/*Define the game stages*/
typedef enum
{
    /*The start stage of the game*/
    START,
    /*The game playing stage of the game*/
    PLAYING,
    /*The end of the game*/
    END
} game_stage_t;

int main (void)
{
    game_stage_t stage = START;
    system_init();
    pacer_init(PACER_RATE);
    comment_init();
    intro_com();

    while(1)
    {
        pacer_wait();
        if (stage == START) {
            tinygl_update();
        } else if (stage == PLAYING) {

        } else {

        }
    }
    return 0;
}
