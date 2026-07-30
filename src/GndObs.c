#include "GndObs.h"

//这里是部分误差ps测试得出 对于恐龙 x0是前- x1是后+ y0是上+ y1是下- 本质上就是缩小碰撞范围
const int Gnddx[GndObsVar][2] = { {10,30}, {10,0}, {25,0}, {20,0}, {20,0} };/////////////////////////////////////////////////////!!!!测试
const int Gnddy[GndObsVar][2] = { {0,0}, {5,0}, {5,0}, {0,0}, {5,0} };/////////////////////////////////////////////////////!!!!测试
SDL_Texture *GndObsTexture[GndObsVar];
SDL_Surface *GndObsSurface[GndObsVar];

void AddGndObs(GndObss *pGndObs) {
    pGndObs->type = rand() % GndObsVar;
    GetDrectFromSurface(GndObsSurface[pGndObs->type],
        &pGndObs->rect, 1, 1, 1);//可以加系数
    pGndObs->rect.x = OthBorn_x;
    pGndObs->rect.y = BornedRect.y - pGndObs->rect.h + GndObsFootdy;
}
