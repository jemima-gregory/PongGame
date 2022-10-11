#include "system.h"
#include "navswitch.h"
#include "ir_uart.h"
#include "tinygl.h"

#include "stage.h"
#include "comment.h"

static int comment_count = 0;

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
    if (comment_count == 1) {

    }

    return PLAYING;
}

game_stage_t end_stage(void)
{
    return END
}