/*
    File:    comment.h
    Authors: Jee Park, Jemima Gregory
    Date:    10 October 2022
    Descr:   Contains functions to display all the comments that are displayed throughout the game
*/

#ifndef COMMENT_H
#define COMMENT_H

/** Initialize comment */
void comment_init(void);

/** Set the display to the intro text */
void comment_intro(void);

/** Set the display to the score text 
    @param the current player score */
void comment_score(char score);

/** Set the display to the end text */
void comment_end(void);

#endif