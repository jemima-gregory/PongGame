/*
    File:    stage.h
    Authors: Jee Park, Jemima Gregory
    Date:    11 October 2022
    Descr:   Contains the game logic and functionality for each of the stages of play
*/

#ifndef STAGE_H
#define STAGE_H

#include "stdint.h"

/** The stages enum */
typedef enum {
    //The start stage of the game
    START,
    //The game playing stage of the game
    PLAYING,
    //The end of the game
    END
} game_stage_t;

/** The start stage of the game 
    @return the next stage */
game_stage_t stage_start(void);

/** The playing stage is where the actual game is displayed and managed 
    @return the next stage */
game_stage_t stage_playing (int8_t call_ball);

/** The end stage of the game 
    @return the next stage */
game_stage_t stage_end (void);

#endif