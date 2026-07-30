#include "SkyObs.h"

SDL_Surface *SkyObsSurface = NULL;
SDL_Texture *SkyObsTexture = NULL;
SDL_Rect SkyObsRect_wh;
const int SkyDirecY[SkyDirectVar] = { 200, 300, 350, 400 };
const int Skydx[2] = { 5,5 };
const int Skydy[2] = { 5,5 };

void AddSkyObs(SkyObss *pSkyObs) {
    pSkyObs->type = rand() % SkyDirectVar;
    pSkyObs->rect = SkyObsRect_wh;
    pSkyObs->rect.x = OthBorn_x;
    pSkyObs->rect.y = SkyDirecY[pSkyObs->type];
}
