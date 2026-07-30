#ifndef SKYOBS_H
#define SKYOBS_H

#include "Base.h"

#define SkyObsMaxN     3
#define SkyObsExp      2
#define SkyObsMaxY     200
#define SkyObsMinY     20
#define SkyObsSizeMin  5
#define SkyObsSizeRang 5
#define SkyObsSpeed    1.5

extern SDL_Surface *SkyObsSurface;
extern SDL_Texture *SkyObsTexture;
extern SDL_Rect SkyObsRect_wh;
#define SkyDirectVar 4
typedef enum
{
    TooHigh,
    High,
    Mid,
    Low
}SkyDirecTypes;
extern const int SkyDirecY[SkyDirectVar];
extern const int Skydx[2];
extern const int Skydy[2];
typedef struct
{
    SDL_Rect rect;
    SkyDirecTypes type;
}SkyObss;

void AddSkyObs(SkyObss *);

#endif
