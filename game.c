#include "system.h"
#include "pacer.h"
#include "comment.h"

#define PACER_RATE 500

int main (void)
{
    system_init();
    pacer_init(PACER_RATE);
    comment_init();
    intro_com();

    while(1)
    {
        pacer_wait();
        tinygl_update();
    }
    return 0;
}
