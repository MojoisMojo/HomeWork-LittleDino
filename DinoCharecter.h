#ifndef DINOCHARECTER_H
#define DINOCHARECTER_H

#define DinoTaildx 16 //Tail lenth
#define DinoLegdy 15 //Leg lenth
#define DinoFootdy 5  //the foot distance from the bottum of DinoRect
#define JumpLine_y 151 //the top of dino 
#define DinoVar 6
#define DinoCoe 0.8
const int DionWideth = 190, DinoHeight = 150;//in the Org Picture too lazy to chage...
typedef enum
{
    Air,
    StandL,
    StandR,
    CrawlL,
    CrawlR,
    Dead
}DinoTypes;
const int DinoRelativeWide[DinoVar] = { 95 * DinoCoe, 127 * DinoCoe,
 127 * DinoCoe, 173 * DinoCoe, 173 * DinoCoe, 127 * DinoCoe };
DinoTypes DinoSta = Air;
SDL_Surface *DinoSurface = NULL;
SDL_Texture *DinoTexture = NULL;
SDL_Rect DinoDrect;
SDL_Rect DinoSrect[DinoVar];

// bool IsJump = false;
bool IsCrawl = false;
bool IsJump = false;
bool DoubleJump = false;
double JumpSpeed = -2.0;

/*------------------------ Function --------------------------*/
int cntDinoDelay = 0;
#define DinoDelay 3

void PaintDino();
void GravDino();
void MoveDino();

void PaintDino() {
    SDL_RenderCopy(Renderer, DinoTexture, DinoSrect + DinoSta, &DinoDrect);
}

void GravDino() {
    if (JumpSpeed < 3.0)
        JumpSpeed += GraAc;
    if (DinoDrect.y + DinoDrect.h >= BornedRect.y - 30)
    {
        DinoDrect.y = BornedRect.y - DinoDrect.h;
        JumpSpeed = 0;
        DinoSta = StandL;
        DoubleJump = false;
    }
}
void MoveDino() {
    if (DinoSta == Air)
    {
        GravDino();
        Move(&DinoDrect.y, JumpSpeed, MoveD);
        return;
    }
    if ((++cntDinoDelay) % DinoDelay)
        return;
    switch (DinoSta)
    {
    case StandL:
        DinoSta = StandR;
        break;
    case StandR:
        DinoSta = StandL;
        break;
    case CrawlL:
        DinoSta = CrawlR;
        break;
    case CrawlR:
        DinoSta = CrawlL;
        break;
    default:
        break;
    }

}

#endif