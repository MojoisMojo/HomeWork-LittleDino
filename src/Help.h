#ifndef HELP_H
#define HELP_H

#include "Base.h"

#define RuleMaxN 6
extern char Rulechar[25];
extern SDL_Rect RuleRect;
//help
void HelpUI(bool *);
void PaintRule(int *index);

#endif
