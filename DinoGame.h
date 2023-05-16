#ifndef DINOGAME_H
#define DINOGAME_H
#include "Base.h"
#include "Box.h"
#include "Help.h"
/*-------------------- BackGround -----------------------*/
#include "BGD.h"

/*----------------------------- Font --------------------------------*/
#include "WordsAndFont.h"

/*---------------------- Player -------------------------*/
#include "DinoCharecter.h"

/*------------------------ Obstacle ---------------------------*/
#include "Obs.h"

/*--------------------------- Function ------------------------------*/

/****************** The UI ******************/
//enter
void MainUI();
//to play
void PlayUI();
void InPlay();
void LoseUI();
//pause play
void PauseUI();



/************** Game Details **************/

//----------------------------------Logic
bool CheckSingCollision(const SDL_Rect *ObsRect, const int dx[2], const int dy[2]);
bool CheckCollisions();

//---------------------------------Move Picture
void MoveAll();

//-----------------------------------Paint
void PaintMenu();
void PaintAll();

/********* ReInitialize *********/
//to reset playui
void ResetBasic();
void ResetPlay();

/************ Base *************/
//begin the game
void BEGIN();
//load the picture
void LOAD();
//destroy and quit
void QUIT();

#undef main
#endif