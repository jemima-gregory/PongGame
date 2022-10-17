/*
    File:    comment.c
    Authors: Jee Park, Jemima Gregory
    Date:    10 October 2022
    Descr:   Contains functions to display all the comments that are displayed throughout the game
*/

#include "system.h"
#include "pacer.h"
#include "tinygl.h"
#include "../fonts/font5x5_1.h"
#include "comment.h"

#define PACER_RATE 500
#define MESSAGE_RATE 30

//Initialize comment
void comment_init (void)
{
    tinygl_init(PACER_RATE);
    tinygl_font_set(&font5x5_1);
    tinygl_text_speed_set(MESSAGE_RATE);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    tinygl_text_dir_set(TINYGL_TEXT_DIR_ROTATE);
}

//Set the display to the intro text
void comment_intro(void) {
    tinygl_text("  Push to start");
}

//Set the display to the score text
void comment_score(char score) 
{
    tinygl_point_t point = {0, 0};
    char display_score[1];
    display_score[0] = score;
    tinygl_draw_message(display_score, point, 1);
}

//Set the display to the end text
void comment_end(void) 
{
    tinygl_text("Thank you for playing");
}
