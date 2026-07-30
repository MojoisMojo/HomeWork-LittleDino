#ifndef DINOCHARECTER_H
#define DINOCHARECTER_H

#include "Base.h"

#define DinoTaildx 16 //Tail lenth
#define DinoLegdy 15 //Leg lenth
#define DinoFootdy 5  //the foot distance from the bottum of DinoRect
#define JumpLine_y 151 //the top of dino
#define DinoVar 6
#define DinoCoe 0.8
extern const int DionWideth;
extern const int DinoHeight;//in the Org Picture too lazy to chage...
typedef enum
{
    Air,
    StandL,
    StandR,
    CrawlL,
    CrawlR,
    Dead
}DinoTypes;
extern const int DinoRelativeWide[DinoVar];
extern DinoTypes DinoSta;
extern SDL_Surface *DinoSurface;
extern SDL_Texture *DinoTexture;
extern SDL_Rect DinoDrect;
extern SDL_Rect DinoSrect[DinoVar];

// bool IsJump = false;
extern bool IsCrawl;
extern bool IsJump;
extern bool DoubleJump;
extern double JumpSpeed;

/*------------------------ Function --------------------------*/
extern int cntDinoDelay;
#define DinoDelay 3

void PaintDino();
void GravDino();
void MoveDino();

#endif
