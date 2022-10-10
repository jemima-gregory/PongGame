#include "system.h"
#include "pacer.h"
#include "tinygl.h"
#include "../fonts/font5x5_1.h"

#define PACER_RATE 500
#define MESSAGE_RATE 10

void comment_init (void)
{
    tinygl_init(PACER_RATE);
}

void intro_com (void) {
    tinygl_point_t point = {0, 6};
    tinygl_font_set(&font5x5_1);
    tinygl_text_speed_set(MESSAGE_RATE);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    tinygl_text_dir_set(TINYGL_TEXT_DIR_ROTATE);
    tinygl_draw_message("Click button to play...", point, 1);
}