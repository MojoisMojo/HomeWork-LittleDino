#ifndef BASE_H
#define BASE_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <string.h>

#define MyMax(a,b) (a) > (b) ? (a) : (b)
#define MyMin(a,b) (a) < (b) ? (a) : (b)
#define MySwap(a,b) \
    do { \
        int tempofswap = (a); \
        (a) = (b); \
        (b) = tempofswap; \
    } while (0)
//boundary
#define wideth 1200
#define height 600

extern const int EachStep;
extern double AcSpeed;
#define Acdv 1e-3
#define GraAc 0.2

#define Horizon_dy 55 //the horizon's distance from the bottom
#define Sky_y 150 //the lowest of the sky

#define MoveR  1
#define MoveD  1
#define MoveL -1
#define MoveU -1
#define dita 5

#define OthBorn_x (2 * AcSpeed * EachStep + wideth)

extern int DelayTime;
extern SDL_Event MainEvent;
extern bool IsLose;
extern bool Isinvincibe;
extern bool AllQuit;
extern bool PlayQuit;

enum
{
    _1st,
    _2nd,
    _3rd,
    _4th,
    _5th,
    _6th
};

extern SDL_Window *Window;
extern SDL_Renderer *Renderer;

/*********** Calculation Details ***********/

//Score
extern double Score;
extern double MaxScore;
extern int level;
extern FILE *fp;
//Born
extern SDL_Rect BornedRect;
extern int Judge_x;


int PlusMol(int *, int, int);
void Move(int *, double, int);
void GetDrectFromSurface(SDL_Surface *, SDL_Rect *, double, int, int);
bool CheckDisappear(const SDL_Rect *);
void CalScoreandLevel();

//num + plus in【0，mol）
#endif
