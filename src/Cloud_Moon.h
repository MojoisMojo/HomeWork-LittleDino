#ifndef CLOUD_MOON_H
#define CLOUD_MOON_H

#include "Base.h"

//this is for cloud & Moon
#define CloudMaxN     4
#define CloudExp      2
#define CloudMaxY     200
#define CloudMinY     20
#define CloudSizeMin  5
#define CloudSizeRang 5
#define CloudInterval 200 //interval to show a new
#define CloudSpeed    0.6
extern int cntCloudInterval; //cnt
extern SDL_Surface *CloudSurface;
extern SDL_Texture *CloudTexture;
typedef struct clouds // it is a Queue
{
    double CSpeed;
    double CSize;
    SDL_Rect CRect;
}Clouds;
extern int cntCloud;//the number of cloud shown
extern int indexCloud;//index of the array
extern Clouds Cloud[CloudMaxN];

void InitCloud();
void SetOutCloud();
void RefreshCloud();

#define MoonSpeed 0.7
extern SDL_Surface *MoonSurface;
extern SDL_Texture *MoonTexture;
extern SDL_Rect MoonRect;

#endif
