#ifndef STAGE_H
#define STAGE_H


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

game_stage_t start_stage(void);

game_stage_t playing_stage(void);

game_stage_t end_stage(void);

#endif