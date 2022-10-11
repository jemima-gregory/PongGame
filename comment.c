#include "system.h"
#include "pacer.h"
#include "tinygl.h"
#include "../fonts/font5x5_1.h"
#include "comment.h"

#define PACER_RATE 500
#define MESSAGE_RATE 30

void comment_init (void)
{
    tinygl_init(PACER_RATE);
    tinygl_font_set(&font5x5_1);
    tinygl_text_speed_set(MESSAGE_RATE);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    tinygl_text_dir_set(TINYGL_TEXT_DIR_ROTATE);
}

void intro_com (void) {
    tinygl_text("  Push to start");
}

void score (char score1, char score2) 
{
    tinygl_point_t point = {0, 0};
    tinygl_draw_message("score1 : score2", point, 1);
}