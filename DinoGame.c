#include "DinoGame.h"

int main(int argc, char *argv[]) {
    BEGIN();
    LOAD();
    MainUI();
    QUIT();
}

/********************************* The UI *********************************/
void MainUI() {
    printf("MainUI\n");
    ResetBasic();
    AllQuit = false;
    PaintAll();
    while (!AllQuit)
    {
        while (SDL_PollEvent(&MainEvent))
        {
            switch (MainEvent.type)
            {
            case SDL_QUIT:
                AllQuit = true;
                break;
            case SDL_MOUSEBUTTONDOWN:
                break;
            case SDL_MOUSEBUTTONUP:
                if (MainEvent.button.x >= 390 && MainEvent.button.x <= 805
                    && MainEvent.button.y >= 366 && MainEvent.button.y <= 517)
                {
                    if (MainEvent.button.y <= 444
                        || (MainEvent.button.x >= 484 && MainEvent.button.x <= 711))
                        PlayUI();
                } else if (MainEvent.button.x <= 183 && MainEvent.button.y >= 545)
                {
                    HelpUI(&AllQuit);
                    PaintAll();
                }
                break;
            case SDL_KEYDOWN:
                switch (MainEvent.key.keysym.sym)
                {
                case SDLK_q:
                case SDLK_ESCAPE:
                    AllQuit = true;
                    break;
                case SDLK_h:
                    HelpUI(&AllQuit);
                    break;
                default:
                    PlayUI();
                    break;
                }
                break;
            default:
                break;
            }
            PaintAll();
        }
    }
}

void PlayUI() {
    printf("PlayUI\n");
    PlayQuit = false;
    while (!PlayQuit)
    {
        InPlay();
        if (IsLose)
            LoseUI();
    }
    ResetPlay();
}

void InPlay() {
    ResetPlay();
    PlayQuit = false;
    DinoSta = StandL;
    while (!PlayQuit && !AllQuit)
    {
        MoveAll();
        PaintAll();
        if (!Isinvincibe && CheckCollisions())
        {
            if (IsCrawl)
                DinoDrect.x += DinoRelativeWide[CrawlL] - DinoRelativeWide[StandL];
            IsCrawl = false;
            IsLose = true;
            PlayQuit = true;
            DinoSta = Dead;
            return;
        }
        SDL_Delay(DelayTime);
        while (SDL_PollEvent(&MainEvent))
        {
            switch (MainEvent.type)
            {
            case SDL_QUIT:
                PlayQuit = true;
                AllQuit = true;
                break;
            case SDL_KEYDOWN:
                switch (MainEvent.key.keysym.sym)
                {
                case SDLK_q:
                case SDLK_ESCAPE:
                    PlayQuit = true;
                    break;
                case SDLK_h:
                    HelpUI(&PlayQuit);
                    PaintAll();
                    break;
                case SDLK_p:
                    PauseUI();
                    break;
                case SDLK_s:
                case SDLK_DOWN:
                    switch (DinoSta)
                    {
                    case Air:
                        JumpSpeed = 3.0;
                        break;
                    case StandL:
                        IsCrawl = true;
                        DinoSta = CrawlR;
                        break;
                    case StandR:
                        IsCrawl = true;
                        DinoSta = CrawlL;
                        break;
                    default:
                        break;
                    }
                    break;
                case SDLK_w:
                case SDLK_UP:
                case SDLK_SPACE:
                    switch (DinoSta)
                    {
                    case StandL:
                    case StandR:
                        DinoSta = Air;
                        JumpSpeed = -2.1;
                        Move(&DinoDrect.y, JumpSpeed, MoveD);
                        break;
                    case Air:
                        if (Isinvincibe || (!DoubleJump && level > 3))
                        {
                            DoubleJump = true;
                            JumpSpeed = -1.8;
                            Move(&DinoDrect.y, JumpSpeed, MoveD);
                        }
                        break;
                    default:
                        break;
                    }
                    break;
                default:
                    break;
                }
                break;
            case SDL_KEYUP:
                if (!IsCrawl)
                    break;
                switch (MainEvent.key.keysym.sym)
                {
                case SDLK_s:
                case SDLK_DOWN:
                    if (MainEvent.type == SDL_KEYDOWN &&
                        (MainEvent.key.keysym.sym == SDLK_s || MainEvent.key.keysym.sym == SDLK_DOWN))
                        break;
                    IsCrawl = false;
                    DinoSta = StandL;
                default:
                    break;
                }
            default:
                break;
            }
        }
    }
}

void LoseUI() {
    PaintAll();
    SDL_RenderCopy(Renderer, BlankTexture, NULL, NULL);
    SDL_RenderCopy(Renderer, LoseTexture, NULL, &BoxRect);
    SDL_RenderPresent(Renderer);
    while (1)
    {
        while (SDL_PollEvent(&MainEvent))
        {
            switch (MainEvent.type)
            {
            case SDL_QUIT:
                AllQuit = true;
                return;
            case SDL_MOUSEBUTTONUP:
                if (MainEvent.button.x >= 452 && MainEvent.button.x <= 746
                    && MainEvent.button.y >= 370 && MainEvent.button.y <= 437)
                {
                    if (MainEvent.button.x >= 675)
                    {
                        PlayQuit = false;
                        return;
                    } else if (MainEvent.button.x <= 521)
                        return;
                }
                break;
            case SDL_KEYDOWN:
                switch (MainEvent.key.keysym.sym)
                {
                case SDLK_RETURN:
                case SDLK_r:
                    PlayQuit = false;
                case SDLK_ESCAPE:
                case SDLK_q:
                    return;
                default:
                    break;
                }
            default:
                break;
            }
        }
    }

}

void PauseUI() {
    PaintAll();
    SDL_RenderCopy(Renderer, BlankTexture, NULL, NULL);
    SDL_RenderCopy(Renderer, PauseTexture, NULL, &BoxRect);
    SDL_RenderPresent(Renderer);
    bool PauseQuit = false;
    while (!PauseQuit)
    {
        while (SDL_PollEvent(&MainEvent))
        {
            switch (MainEvent.type)
            {
            case SDL_QUIT:
                AllQuit = true;
                PlayQuit = true;
                return;
            case SDL_MOUSEBUTTONUP:
                if (MainEvent.button.x >= 452 && MainEvent.button.x <= 746
                    && MainEvent.button.y >= 370 && MainEvent.button.y <= 437)
                {
                    if (MainEvent.button.x >= 565 && MainEvent.button.x <= 627)
                        return;
                    else if (MainEvent.button.x >= 675)
                    {
                        ResetPlay();
                        PlayQuit = false;
                        PaintAll();
                        return;
                    } else if (MainEvent.button.x <= 521)
                    {
                        PlayQuit = true;
                        return;
                    }
                }
                break;
            case SDL_KEYDOWN:
                switch (MainEvent.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                case SDLK_q:
                    PlayQuit = true;
                    return;
                case SDLK_p:
                case SDLK_RETURN:
                    return;
                case SDLK_r:
                    ResetPlay();
                    PlayQuit = false;
                    PaintAll();
                    return;
                case SDLK_h:
                    HelpUI(&PauseQuit);
                    break;
                default:
                    break;
                }
            default:
                break;
            }
            PaintAll();
            SDL_RenderCopy(Renderer, BlankTexture, NULL, NULL);
            SDL_RenderCopy(Renderer, PauseTexture, NULL, &BoxRect);
            SDL_RenderPresent(Renderer);
        }
    }
}



/*****************************  Game Details  *****************************/

/* ------------------------- Logic ----------------------- */

bool CheckSingCollision(const SDL_Rect *ObsRect, const int dx[2], const int dy[2]) {
    if (BornedRect.x + DinoRelativeWide[DinoSta] - dx[0] <= ObsRect->x
        || BornedRect.x + DinoTaildx + dx[1] >= ObsRect->x + ObsRect->w)
        return false;
    if (DinoDrect.y + DinoDrect.h - DinoFootdy - DinoLegdy - dy[0] <= ObsRect->y
        || DinoDrect.y + dy[1] >= ObsRect->y + ObsRect->h)
        return false;
    return true;
}

bool CheckCollisions() {
    Obss *pObs = ObsHead.next;
    for (int i = cntObs; i > 0; i--, pObs = pObs->next)
    {
        switch (pObs->type)
        {
        case GND:
            if (CheckSingCollision(&pObs->Gnd.rect, Gnddx[pObs->Gnd.type], Gnddy[pObs->Gnd.type]))
                return true;
            break;
        case SKY:
            if (IsCrawl)
                return false;
            if (CheckSingCollision(&pObs->Sky.rect, Skydx, Skydy))
                return true;
            break;
        default:
            break;
        }
    }
    return false;
}

/* ---------------------- Move Picture ----------------------- */

void MoveAll() {
    MovBGD();
    MoveObs();
    MoveDino();
}

/*-------------------------Paint------------------------*/

void PaintMenu() {
    SDL_Surface *MenuSurface = IMG_Load("image/menu.png");
    SDL_Texture *MenuTexture = SDL_CreateTextureFromSurface(Renderer, MenuSurface);
    SDL_RenderCopy(Renderer, BlankTexture, NULL, NULL);
    SDL_RenderCopy(Renderer, MenuTexture, NULL, NULL);
    SDL_FreeSurface(MenuSurface);
    SDL_DestroyTexture(MenuTexture);
}

void PaintAll() {
    SDL_RenderClear(Renderer);
    PaintBGD();
    PaintObs();
    PaintScore();
    PaintLevel();
    PaintDino();
    if (PlayQuit && !IsLose)
        PaintMenu();
    SDL_RenderPresent(Renderer);
}

/**************************** ReInitialize ****************************/
//重置
void ResetBasic() {
    IsCrawl = false;
    IsJump = false;
    DoubleJump = false;
    IsLose = false;
    PlayQuit = true;
    DinoSta = Air;
    Judge_x = BornedRect.x + DinoRelativeWide[DinoSta];
    DinoDrect.x = BornedRect.x;
    DinoDrect.y = BornedRect.y - DinoDrect.h;
    MaxScore = MyMax(MaxScore, Score);
    Score = 0;
    level = 0;
    AcSpeed = 1.0;
}

void ResetPlay() {
    ResetBasic();
    ResetObs();
}

/******************************** Base ********************************/

void BEGIN() {
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);//忽视事件处理与内存占用!!!
    Window =
        SDL_CreateWindow("DinoGame",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            wideth, height,
            SDL_WINDOW_SHOWN);
    Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
}

// load evey needed src
void LOAD() {
    fp = fopen("data/Win.txt", "r");
    char *winchar = (char *)malloc(sizeof(char) * 20);
    if (fp && fscanf(fp, "%s", winchar) != EOF && !strcmp(winchar, "MojoMojowinwinwin"))
        Isinvincibe = true;
    free(winchar);
    if (fp)
        fclose(fp);

    //this is for background
    MainBackGroundSurface = IMG_Load("image/MBNG.png");
    MainBackGroundTexture = SDL_CreateTextureFromSurface(Renderer, MainBackGroundSurface);//纹理到画笔
    MainBackGroundDrect.w = MainBackGroundSrect.w = wideth;
    MainBackGroundDrect.h = MainBackGroundSrect.h = height;
    MainBackGroundSrect.y = (MainBackGroundSurface->h - height) / 2;

    LoseSurface = IMG_Load("image/BoxEnd.png");
    PauseSurface = IMG_Load("image/BoxPause.png");
    LoseTexture = SDL_CreateTextureFromSurface(Renderer, LoseSurface);
    PauseTexture = SDL_CreateTextureFromSurface(Renderer, PauseSurface);
    GetDrectFromSurface(LoseSurface, &BoxRect, 1, 1, 1);
    BoxRect.x = (wideth - BoxRect.w) / 2;
    BoxRect.y = (height - BoxRect.h) / 2;

    BlankSurface = IMG_Load("image/white.png");
    BlankTexture = SDL_CreateTextureFromSurface(Renderer, BlankSurface);

    ScoreFont = TTF_OpenFont("font/GenshinDefault.ttf", FontSize);

    //for borned
    BornedRect.x = wideth / 20;
    BornedRect.y = height - Horizon_dy;//左下角


    //Moon&Cloud
    MoonSurface = IMG_Load("image/Moon.png");
    MoonTexture = SDL_CreateTextureFromSurface(Renderer, MoonSurface);
    GetDrectFromSurface(MoonSurface, &MoonRect, 1, 1, 1);
    MoonRect.x = rand() % (wideth - MoonRect.w);
    MoonRect.y = Sky_y - MoonRect.h;

    CloudSurface = IMG_Load("image/cloud.png");
    SDL_SetColorKey(CloudSurface, SDL_TRUE, SDL_MapRGB(CloudSurface->format, 255, 255, 255));
    CloudTexture = SDL_CreateTextureFromSurface(Renderer, CloudSurface);
    InitCloud();

    //Dino
    DinoSurface = IMG_Load("image/dinohh.png");
    DinoTexture = SDL_CreateTextureFromSurface(Renderer, DinoSurface);
    DinoDrect.w = DionWideth * DinoCoe;
    DinoDrect.h = DinoHeight * DinoCoe;
    DinoDrect.x = BornedRect.x;
    DinoDrect.y = BornedRect.y - DinoDrect.h;
    for (int i = 0; i < DinoVar; i++)
    {
        DinoSrect[i].w = DionWideth;
        DinoSrect[i].h = DinoHeight;
        DinoSrect[i].x = 0;
        DinoSrect[i].y = i * DinoHeight;
    }

    GndObsSurface[SingT] = IMG_Load("image/Tree.png");
    SDL_SetColorKey(GndObsSurface[SingT], SDL_TRUE,
        SDL_MapRGB(GndObsSurface[SingT]->format, 255, 255, 255));//white
    GndObsTexture[SingT] = SDL_CreateTextureFromSurface(Renderer, GndObsSurface[SingT]);

    GndObsSurface[SnowMan] = IMG_Load("image/snowman1.png");
    SDL_SetColorKey(GndObsSurface[SnowMan], SDL_TRUE,
        SDL_MapRGB(GndObsSurface[SnowMan]->format, 0, 0, 0));//black
    GndObsTexture[SnowMan] = SDL_CreateTextureFromSurface(Renderer, GndObsSurface[SnowMan]);

    GndObsSurface[SnowBall] = IMG_Load("image/snowball.png");
    GndObsTexture[SnowBall] = SDL_CreateTextureFromSurface(Renderer, GndObsSurface[SnowBall]);

    GndObsSurface[DoubG] = IMG_Load("image/DoubG.png");
    SDL_SetColorKey(GndObsSurface[DoubG], SDL_TRUE,
        SDL_MapRGB(GndObsSurface[DoubG]->format, 255, 255, 255));//white
    GndObsTexture[DoubG] = SDL_CreateTextureFromSurface(Renderer, GndObsSurface[DoubG]);


    GndObsSurface[TribG] = IMG_Load("image/TribG.png");
    GndObsTexture[TribG] = SDL_CreateTextureFromSurface(Renderer, GndObsSurface[TribG]);

    SkyObsSurface = IMG_Load("image/Bird.png");////////////////
    SDL_SetColorKey(SkyObsSurface, SDL_TRUE,
        SDL_MapRGB(SkyObsSurface->format, 255, 255, 255));//white
    SkyObsTexture = SDL_CreateTextureFromSurface(Renderer, SkyObsSurface);
    GetDrectFromSurface(SkyObsSurface, &SkyObsRect_wh, 0.6, 1, 1);

    fp = fopen("data/MaxScore.txt", "r+");
    fscanf(fp, "%lf", &MaxScore);
    fclose(fp);
}

//delete all
void QUIT() {
    printf("Down!\n");


    SDL_FreeSurface(MainBackGroundSurface);
    SDL_FreeSurface(CloudSurface);
    SDL_FreeSurface(MoonSurface);
    SDL_FreeSurface(DinoSurface);
    for (int i = 0; i < GndObsVar; i++)
        SDL_FreeSurface(GndObsSurface[i]);
    SDL_FreeSurface(SkyObsSurface);
    SDL_FreeSurface(LoseSurface);
    SDL_FreeSurface(PauseSurface);
    SDL_FreeSurface(BlankSurface);

    SDL_DestroyTexture(MainBackGroundTexture);
    SDL_DestroyTexture(CloudTexture);
    SDL_DestroyTexture(MoonTexture);
    SDL_DestroyTexture(DinoTexture);
    for (int i = 0; i < GndObsVar; i++)
        SDL_DestroyTexture(GndObsTexture[i]);
    SDL_DestroyTexture(SkyObsTexture);
    SDL_DestroyTexture(LoseTexture);
    SDL_DestroyTexture(PauseTexture);
    SDL_DestroyTexture(BlankTexture);


    TTF_CloseFont(ScoreFont);


    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(Window);
    fp = fopen("data/MaxScore.txt", "w+");
    fprintf(fp, "%.lf", MaxScore);
    fclose(fp);

    SDL_Quit();
    exit(0);
}

