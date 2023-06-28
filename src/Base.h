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
        int tempofswap = (a); \
        (a) = (b);\
        (b) = t;\
srand(time(NULL));
//boundary
#define wideth 1200
#define height 600

const int EachStep = 18;
double AcSpeed = 1.0;
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

int DelayTime = 30;
SDL_Event MainEvent;
bool IsLose = false;
bool Isinvincibe = false;
bool AllQuit = false;
bool PlayQuit = true;

enum
{
    _1st,
    _2nd,
    _3rd,
    _4th,
    _5th,
    _6th
};

SDL_Window *Window = NULL;
SDL_Renderer *Renderer = NULL;

/*********** Calculation Details ***********/

//Score
double Score = 0;
double MaxScore = 0;
int level = 0;
FILE *fp;
//Born
SDL_Rect BornedRect;
int Judge_x;


int PlusMol(int *, int, int);
void Move(int *, double, int);
void GetDrectFromSurface(SDL_Surface *, SDL_Rect *, double, int, int);
bool CheckDisappear(const SDL_Rect *);
void CalScoreandLevel();

//num + plus in【0，mol）
int PlusMol(int *num, int plus, int mol) {
    return *num = (*num + plus) % mol;
}

/*Coe is the coefficient of the scale factor(缩放系数),
wdiv and hdiv is how many parts of the picture*/
void GetDrectFromSurface(SDL_Surface *Surface, SDL_Rect *Drect, double Coe, int wdiv, int hdiv) {
    Drect->w = Surface->w * Coe / wdiv;
    Drect->h = Surface->h * Coe / hdiv;
}

void Move(int *derc, double Speed, int MoveDir) {
    *derc = *derc + Speed * EachStep * MoveDir;
}

bool CheckDisappear(const SDL_Rect *Rect) {
    return Rect->x + Rect->w <= 0;
}

void CalScoreandLevel() {
    Score += AcSpeed / 2;
    level = Score / 100;
    if (level < 3)
        AcSpeed = level * 0.1 + 1;
    else if (level < 8) // 
        AcSpeed = 1.15 + level * 0.05;
    else if (AcSpeed <= 2.5)
        AcSpeed = 1.39 + 0.02 * level;

}
#endif