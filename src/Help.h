#ifndef HELP_H
#define HELP_H
#define RuleMaxN 6
char Rulechar[25];
SDL_Rect RuleRect;
//help
void HelpUI(bool *);
void PaintRule(int *index);

void PaintRule(int *index) {
    sprintf(Rulechar, "image/rule%d.png", *index);
    SDL_Surface *RuleSurface = IMG_Load(Rulechar);
    SDL_Texture *RuleTexture = SDL_CreateTextureFromSurface(Renderer, RuleSurface);
    GetDrectFromSurface(RuleSurface, &RuleRect, 1, 1, 1);
    RuleRect.x = (wideth - RuleRect.w) / 2;
    RuleRect.y = (height - RuleRect.h) / 2;

    SDL_RenderCopy(Renderer, RuleTexture, NULL, &RuleRect);
    SDL_RenderPresent(Renderer);

    SDL_FreeSurface(RuleSurface);
    SDL_DestroyTexture(RuleTexture);
}
void HelpUI(bool *quit) {
    int index = 0;
    SDL_RenderCopy(Renderer, BlankTexture, NULL, NULL);
    PaintRule(&index);
    while (1)
    {
        while (SDL_PollEvent(&MainEvent))
        {
            switch (MainEvent.type)
            {
            case SDL_QUIT:
                AllQuit = true;
                PlayQuit = true;
                *quit = true;
                return;
            case SDL_MOUSEBUTTONUP:
                if (MainEvent.button.y >= 476 && MainEvent.button.y <= 525
                    && MainEvent.button.x >= 394 && MainEvent.button.x <= 800)
                {
                    if (MainEvent.button.x <= 442)
                        PlusMol(&index, RuleMaxN - 1, RuleMaxN);
                    else if (MainEvent.button.x >= 754)
                        PlusMol(&index, 1, RuleMaxN);
                }
                else if (MainEvent.button.y >= 71 && MainEvent.button.y <= 100
                    && MainEvent.button.x >= 918 && MainEvent.button.x <= 951)
                    return;
                break;
            case SDL_KEYDOWN:
                switch (MainEvent.key.keysym.sym)
                {
                case SDLK_q:
                case SDLK_ESCAPE:
                    return;
                case SDLK_w:
                case SDLK_UP:
                case SDLK_LEFT:
                case SDLK_a:
                    PlusMol(&index, RuleMaxN - 1, RuleMaxN);
                    break;
                case SDLK_RETURN:
                case SDLK_RIGHT:
                case SDLK_d:
                case SDLK_DOWN:
                case SDLK_s:
                    PlusMol(&index, 1, RuleMaxN);
                    break;
                }
                break;
            default:
                break;
            }
            PaintRule(&index);
        }
    }
}
#endif