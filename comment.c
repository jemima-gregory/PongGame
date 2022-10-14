#include "system.h"
#include "pacer.h"
#include "tinygl.h"
#include "../fonts/font5x5_1.h"
#include "comment.h"

#define PACER_RATE 500
#define MESSAGE_RATE 30

// Initialize comment
void comment_init (void)
{
    tinygl_init(PACER_RATE);
    tinygl_font_set(&font5x5_1);
    tinygl_text_speed_set(MESSAGE_RATE);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    tinygl_text_dir_set(TINYGL_TEXT_DIR_ROTATE);
}

// Set the display to the intro text
void comment_intro(void) {
    tinygl_text("  Push to start");
}

// Set the display to the score text
void comment_score(char score1, char score2) 
{
    tinygl_point_t point = {0, 6};
    char score_com[] = " s : s ";
    score_com[1] = score1;
    score_com[5] = score2;
    tinygl_draw_message(score_com, point, 1);
}

// Set the display to the end text
void comment_end(void) 
{
    tinygl_text("Thank you for playing");
}
