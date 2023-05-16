#ifndef SKYOBS_H
#define SKYOBS_H

#define SkyObsMaxN     3
#define SkyObsExp      2
#define SkyObsMaxY     200
#define SkyObsMinY     20
#define SkyObsSizeMin  5
#define SkyObsSizeRang 5
#define SkyObsSpeed    1.5

SDL_Surface *SkyObsSurface = NULL;
SDL_Texture *SkyObsTexture = NULL;
SDL_Rect SkyObsRect_wh;
#define SkyDirectVar 4
typedef enum
{
    TooHigh,
    High,
    Mid,
    Low
}SkyDirecTypes;
const int SkyDirecY[SkyDirectVar] = { 200, 300, 350, 400 };
const int Skydx[2] = { 5,5 };
const int Skydy[2] = { 5,5 };
typedef struct
{
    SDL_Rect rect;
    SkyDirecTypes type;
}SkyObss;

void AddSkyObs(SkyObss *);

void AddSkyObs(SkyObss *pSkyObs) {
    pSkyObs->type = rand() % SkyDirectVar;
    pSkyObs->rect = SkyObsRect_wh;
    pSkyObs->rect.x = OthBorn_x;
    pSkyObs->rect.y = SkyDirecY[pSkyObs->type];
}

#endif