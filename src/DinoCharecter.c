#include "DinoCharecter.h"

const int DionWideth = 190, DinoHeight = 150;//in the Org Picture too lazy to chage...
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

int cntDinoDelay = 0;
static bool IsDownHeld() {
    const Uint8 *keyboardState = SDL_GetKeyboardState(NULL);
    return keyboardState[SDL_SCANCODE_S] || keyboardState[SDL_SCANCODE_DOWN];
}

void PaintDino() {
    SDL_RenderCopy(Renderer, DinoTexture, DinoSrect + DinoSta, &DinoDrect);
}

void GravDino() {
    bool downHeld = IsDownHeld();
    if (JumpSpeed < 3.0)
        JumpSpeed += GraAc;
    if (DinoDrect.y + DinoDrect.h >= BornedRect.y - 30)
    {
        DinoDrect.y = BornedRect.y - DinoDrect.h;
        JumpSpeed = 0;
        IsCrawl = downHeld;
        DinoSta = downHeld ? CrawlR : StandL;
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
