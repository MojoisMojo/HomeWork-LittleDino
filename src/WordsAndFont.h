#ifndef WORDSANDFONT_H
#define WORDSANDFONT_H

#include "Base.h"

#define FontSize 36
extern TTF_Font *ScoreFont;
extern SDL_Color FontColor;
extern SDL_Rect ScoreRect;
extern SDL_Rect LevelRect;

extern char ScoreChar[25];
extern char LevelChar[10];

void PaintLevel();
void PaintScore();

#endif
