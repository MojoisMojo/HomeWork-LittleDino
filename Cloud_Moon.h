#ifndef CLOUD_MOON_H
#define CLOUD_MOON_H

//this is for cloud & Moon
#define CloudMaxN     4
#define CloudExp      2
#define CloudMaxY     200
#define CloudMinY     20
#define CloudSizeMin  5
#define CloudSizeRang 5
#define CloudInterval 200 //interval to show a new
#define CloudSpeed    0.6
int cntCloudInterval = 0; //cnt
SDL_Surface *CloudSurface = NULL;
SDL_Texture *CloudTexture = NULL;
typedef struct clouds // it is a Queue
{
    double CSpeed;
    double CSize;
    SDL_Rect CRect;
}Clouds;
int cntCloud = 0;//the number of cloud shown 
int indexCloud = -1;//index of the array
Clouds Cloud[CloudMaxN];

void InitCloud();
void SetOutCloud();
void RefreshCloud();

#define MoonSpeed 0.7
SDL_Surface *MoonSurface = NULL;
SDL_Texture *MoonTexture = NULL;
SDL_Rect MoonRect;

void InitCloud() {
    for (int i = 0; i < CloudMaxN; i++)
    {
        Cloud[i].CSize = 0.1 * (rand() % CloudSizeRang + CloudSizeMin);
        Cloud[i].CSpeed = CloudSpeed;
        GetDrectFromSurface(CloudSurface, &(Cloud[i].CRect), Cloud[i].CSize, 1, 1);
        Cloud[i].CRect.x = OthBorn_x;
        Cloud[i].CRect.y = CloudMinY + rand() % (CloudMaxY - CloudMinY);
    }
    cntCloud = 1;
    indexCloud = _1st;
}

void SetOutCloud() {
    if (cntCloud < CloudMaxN && (cntCloud < CloudExp || rand() % 2))//if there are less than 2 clouds or rand1, add 
        cntCloud++;
}
// //if the first Cloud disappears
void RefreshCloud() {
    cntCloud--;
    Cloud[indexCloud].CSize = 0.1 * (rand() % CloudSizeRang + CloudSizeMin);
    Cloud[indexCloud].CSpeed = CloudSpeed;
    GetDrectFromSurface(CloudSurface, &(Cloud[indexCloud].CRect), Cloud[indexCloud].CSize, 1, 1);
    Cloud[indexCloud].CRect.x = OthBorn_x;
    Cloud[indexCloud].CRect.y = CloudMinY + rand() % (CloudMaxY - CloudMinY);
    PlusMol(&indexCloud, 1, CloudMaxN);
    SetOutCloud();
}

#endif