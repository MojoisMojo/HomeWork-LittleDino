#ifndef BGD_H
#define BGD_H

#include "Base.h"
#include "Cloud_Moon.h"

extern SDL_Surface *MainBackGroundSurface;
extern SDL_Texture *MainBackGroundTexture;
extern SDL_Rect MainBackGroundDrect;
extern SDL_Rect MainBackGroundSrect;

void MovBGD();
void PaintBGD();

#endif
