#ifndef GNDOBS_H
#define GNDOBS_H

#include "Base.h"

#define GndObsFootdy 15 //Gound Obs' under Horizon


#define GndObsVar 5
#define GndObsMaxN 3
#define GndObsExp 2
typedef enum
{
    SingT,
    SnowMan,
    SnowBall,
    DoubG,
    TribG,
    // ComB
}GndObsTypes;
//这里是部分误差ps测试得出 对于恐龙 x0是前- x1是后+ y0是上+ y1是下- 本质上就是缩小碰撞范围
extern const int Gnddx[GndObsVar][2];
extern const int Gnddy[GndObsVar][2];
typedef struct
{
    //可以有系数
    GndObsTypes type;
    SDL_Rect rect;
}GndObss;

extern SDL_Texture *GndObsTexture[GndObsVar];
extern SDL_Surface *GndObsSurface[GndObsVar];

#define GndObsSizeMin 7
#define GndObsSizeRag 4

void AddGndObs(GndObss *);

#endif
