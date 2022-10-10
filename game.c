#include "system.h"
#include "pacer.h"
#include "tinygl.h"
#include "../fonts/font3x5_1.h"


#define PACER_RATE 500
#define MESSAGE_RATE 10

int main (void)
{
    system_init();
    tinygl_point_t point = {3, 0};
    /* TODO: Initialise tinygl. */
    tinygl_init(PACER_RATE);
    tinygl_font_set(&font3x5_1);
    tinygl_text_speed_set(MESSAGE_RATE);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    //tinygl_text_dir_set(TINYGL_TEXT_DIR_ROTATE);
    /* TODO: Set the message using tinygl_text().  */
    tinygl_draw_message("Hello", point, 1);



    pacer_init (PACER_RATE);
    while(1)
    {
        if (true) {
            
        }
        pacer_wait();
        tinygl_update();
    }
    return 0;
}
