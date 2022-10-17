/*
    File:    stage.h
    Authors: Jee Park, Jemima Gregory
    Date:    11 October 2022
    Descr:   Contains the game logic and functionality for each of the stages of play
*/

#ifndef STAGE_H
#define STAGE_H

#include "stdint.h"

//Define the game stages
typedef enum
{
    //The start stage of the game
    START,
    //The game playing stage of the game
    PLAYING,
    //The end of the game
    END
} game_stage_t;

//The start stage of the game, displays the intro on the LED matrix
game_stage_t stage_start(void);

//Displays the game on the matrix and also manages the game play
game_stage_t stage_playing (int8_t call_ball);

//Displayes the end screen
game_stage_t stage_end (void);

#endif