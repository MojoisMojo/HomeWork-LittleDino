#include "Base.h"

const int EachStep = 18;
double AcSpeed = 1.0;

int DelayTime = 30;
SDL_Event MainEvent;
bool IsLose = false;
bool Isinvincibe = false;
bool AllQuit = false;
bool PlayQuit = true;

SDL_Window *Window = NULL;
SDL_Renderer *Renderer = NULL;

double Score = 0;
double MaxScore = 0;
int level = 0;
FILE *fp;
SDL_Rect BornedRect;
int Judge_x;

//num + plus in【0，mol）
int PlusMol(int *num, int plus, int mol) {
    return *num = (*num + plus) % mol;
}

/*Coe is the coefficient of the scale factor(缩放系数),
wdiv and hdiv is how many parts of the picture*/
void GetDrectFromSurface(SDL_Surface *Surface, SDL_Rect *Drect, double Coe, int wdiv, int hdiv) {
    Drect->w = Surface->w * Coe / wdiv;
    Drect->h = Surface->h * Coe / hdiv;
}

void Move(int *derc, double Speed, int MoveDir) {
    *derc = *derc + Speed * EachStep * MoveDir;
}

bool CheckDisappear(const SDL_Rect *Rect) {
    return Rect->x + Rect->w <= 0;
}

void CalScoreandLevel() {
    Score += AcSpeed / 2;
    level = Score / 100;
    if (level < 3)
        AcSpeed = level * 0.1 + 1;
    else if (level < 8) //
        AcSpeed = 1.15 + level * 0.05;
    else if (AcSpeed <= 2.5)
        AcSpeed = 1.39 + 0.02 * level;

}
