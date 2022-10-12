#include "system.h"
#include "pacer.h"
#include "tinygl.h"
#include "../fonts/font5x5_1.h"
#include "comment.h"

#define PACER_RATE 500
#define MESSAGE_RATE 50

void comment_init (void)
{
    tinygl_init(PACER_RATE);
    tinygl_font_set(&font5x5_1);
    tinygl_text_speed_set(MESSAGE_RATE);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    tinygl_text_dir_set(TINYGL_TEXT_DIR_ROTATE);
}

void intro_com(void) {
    tinygl_text("  Push to start");
}

void score(char score1, char score2) 
{
    tinygl_point_t point = {0, 0};
    char score_com[] = " : ";
    score_com[0] = score1;
    score_com[2] = score2;
    tinygl_draw_message(score_com, point, 1);
}

void end_com(void) 
{
    tinygl_text("Thank you for playing");
}
