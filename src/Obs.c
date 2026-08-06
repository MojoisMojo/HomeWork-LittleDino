#include "Obs.h"

int cntObs = 0;
int cntObsInterval = 0;
Obss ObsHead, ObsEnd;
Obss Obs[ObsMaxN];

void AddObs() {
    Obss *pObs = (Obss *)malloc(sizeof(Obss));
    pObs->next = &ObsEnd;
    pObs->last = ObsEnd.last;
    ObsEnd.last->next = pObs;
    ObsEnd.last = pObs;
    if (level < 6)
        pObs->type = GND;
    else
        pObs->type = rand() % ObsVar;
    switch (pObs->type)
    {
    case GND:
        AddGndObs(&pObs->Gnd);
        break;
    case SKY:
        AddSkyObs(&pObs->Sky);
        break;
    default:
        break;
    }
}

void DeleteObs(Obss *pObs) {
    cntObs--;
    pObs->last->next = pObs->next;
    pObs->next->last = pObs->last;
    free(pObs);
}

void SetOutObs() {
    if (cntObs < ObsMaxN && (cntObs < ObsExp || rand() % 2))
    {
        cntObs++;
        AddObs();
        if (level < 10)
            cntObsInterval = 0;
        else
            cntObsInterval = rand() % 2 ? 0 : cntObsInterval / 3;
    }
}

void ResetObs() {
    Obss *pObs = ObsEnd.last;
    for (int i = cntObs; i > 0; i--) {
        Obss *last = pObs->last;
        free(pObs);
        pObs = last;
    }
    ObsHead.last = NULL;
    ObsHead.next = &ObsEnd;
    ObsEnd.last = &ObsHead;
    ObsEnd.next = NULL;
    AddObs();
    cntObs = 1;
    cntObsInterval = 0;
}

void MoveObs() {
    Obss *pObs = ObsHead.next;
    for (int i = cntObs; i > 0; i--)
    {
        Obss *next = pObs->next;
        SDL_Rect *rect = NULL;
        switch (pObs->type)
        {
        case GND:
            Move(&pObs->Gnd.rect.x, AcSpeed, MoveL);
            rect = &pObs->Gnd.rect;
            break;
        case SKY:
            Move(&pObs->Sky.rect.x, SkyObsSpeed * AcSpeed, MoveL);
            rect = &pObs->Sky.rect;
            break;
        default:
            break;
        }
        if (CheckDisappear(rect))
            DeleteObs(pObs);
        pObs = next;
    }
    if (!PlusMol(&cntObsInterval, ((level >= 15) ? (rand() % 2) : 0) + 1, ObsInterval))
        SetOutObs();
}

void PaintObs() {
    Obss *pObs = ObsHead.next;
    for (int i = cntObs; i > 0; i--, pObs = pObs->next)
    {
        switch (pObs->type)
        {
        case GND:
            SDL_RenderCopy(Renderer, GndObsTexture[pObs->Gnd.type], NULL, &pObs->Gnd.rect);
            break;
        case SKY:
            SDL_RenderCopy(Renderer, SkyObsTexture, NULL, &pObs->Sky.rect);
            break;
        default:
            break;
        }
    }
}
