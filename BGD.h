#ifndef BGD_H
#define BND_H

SDL_Surface *MainBackGroundSurface = NULL;
SDL_Texture *MainBackGroundTexture = NULL;
SDL_Rect MainBackGroundDrect;
SDL_Rect MainBackGroundSrect;
#include "Cloud_Moon.h"

void MovBGD();
void PaintBGD();

void MovBGD() {
    PlusMol(&(MainBackGroundSrect.x), EachStep * AcSpeed, MainBackGroundSurface->w - wideth);

    CalScoreandLevel();

    Move(&(MoonRect.x), MoonSpeed, MoveL);
    if (CheckDisappear(&MoonRect))
        MoonRect.x = wideth;

    for (int i = indexCloud; i < indexCloud + cntCloud; i++)
        Move(&(Cloud[i % CloudMaxN].CRect.x), Cloud[i % CloudMaxN].CSpeed , MoveL);
    if (!PlusMol(&cntCloudInterval, 1, CloudInterval))
        SetOutCloud();
    if (CheckDisappear(&(Cloud[indexCloud].CRect)))
        RefreshCloud();
}

void PaintBGD() {
    SDL_RenderCopy(Renderer, MainBackGroundTexture,
        &MainBackGroundSrect, &MainBackGroundDrect);

    SDL_RenderCopy(Renderer, MoonTexture, NULL, &MoonRect);

    for (int i = indexCloud; i < indexCloud + cntCloud; i++)
        SDL_RenderCopy(Renderer, CloudTexture,
            NULL, &(Cloud[i % CloudMaxN].CRect));

}

#endif