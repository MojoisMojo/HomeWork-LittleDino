#ifndef OBS_H
#define OBS_H

#include "Base.h"

#define ObsMaxN 3
#define ObsExp 2
#define ObsInterval floor(50 / AcSpeed)
extern int cntObs;
extern int cntObsInterval;

#include "SkyObs.h"
#include "GndObs.h"

#define ObsVar 2
typedef enum
{
    GND,
    SKY
}ObsTypes;

typedef struct obss
{
    ObsTypes type;
    union
    {
        GndObss Gnd;
        SkyObss Sky;
    };
    struct obss *next;
    struct obss *last;
}Obss;

extern Obss ObsHead;
extern Obss ObsEnd;
extern Obss Obs[ObsMaxN];

void AddObs();
void DeleteObs(Obss *);
void SetOutObs();
void ResetObs();
void MoveObs();
void PaintObs();

#endif
