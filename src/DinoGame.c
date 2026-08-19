#ifdef _WIN32
#include <windows.h>
#endif

#include <errno.h>

#include "DinoGame.h"

static bool sdlInitialized = false;
static bool imageInitialized = false;
static bool fontInitialized = false;
static bool gameLoaded = false;

static void ReportStartupError(const char *message, const char *detail) {
    char fullMessage[512];
    if (detail && detail[0] != '\0')
        snprintf(fullMessage, sizeof(fullMessage), "%s\n%s", message, detail);
    else
        snprintf(fullMessage, sizeof(fullMessage), "%s", message);

    fprintf(stderr, "%s\n", fullMessage);
    if (sdlInitialized)
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "DinoGame", fullMessage, Window);
}

static bool LoadSurface(const char *path, SDL_Surface **surface) {
    char message[256];
    *surface = IMG_Load(path);
    if (*surface)
        return true;

    snprintf(message, sizeof(message), "Unable to load image: %s", path);
    ReportStartupError(message, IMG_GetError());
    return false;
}

static bool CreateTexture(const char *path, SDL_Surface *surface, SDL_Texture **texture) {
    char message[256];
    if (!surface) {
        snprintf(message, sizeof(message), "Image was not loaded: %s", path);
        ReportStartupError(message, NULL);
        return false;
    }

    *texture = SDL_CreateTextureFromSurface(Renderer, surface);
    if (*texture)
        return true;

    snprintf(message, sizeof(message), "Unable to create texture: %s", path);
    ReportStartupError(message, SDL_GetError());
    return false;
}

static bool LoadSurfaceAndTexture(const char *path, SDL_Surface **surface, SDL_Texture **texture) {
    return LoadSurface(path, surface) && CreateTexture(path, *surface, texture);
}

static bool ApplyColorKey(const char *path, SDL_Surface *surface, Uint8 red, Uint8 green, Uint8 blue) {
    char message[256];
    if (!surface) {
        snprintf(message, sizeof(message), "Image was not loaded: %s", path);
        ReportStartupError(message, NULL);
        return false;
    }
    if (SDL_SetColorKey(surface, SDL_TRUE,
                        SDL_MapRGB(surface->format, red, green, blue)) == 0)
        return true;

    snprintf(message, sizeof(message), "Unable to configure transparency: %s", path);
    ReportStartupError(message, SDL_GetError());
    return false;
}

static void LoadWinState() {
    char winchar[20];
    FILE *winFile = fopen("data/Win.txt", "r");

    Isinvincibe = false;
    if (!winFile)
        return;

    if (fscanf(winFile, "%19s", winchar) == 1
        && strcmp(winchar, "MojoMojowinwinwin") == 0)
        Isinvincibe = true;
    fclose(winFile);
}

static void LoadMaxScore() {
    double savedScore;
    FILE *scoreFile = fopen("data/MaxScore.txt", "r");

    MaxScore = 0;
    if (!scoreFile)
        return;

    if (fscanf(scoreFile, "%lf", &savedScore) == 1
        && isfinite(savedScore) && savedScore >= 0)
        MaxScore = savedScore;
    fclose(scoreFile);
}

static void SaveMaxScore() {
    FILE *scoreFile = fopen("data/MaxScore.txt", "w");
    if (!scoreFile) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                     "Unable to save MaxScore.txt: %s", strerror(errno));
        return;
    }

    bool writeFailed = fprintf(scoreFile, "%.lf", MaxScore) < 0;
    if (fclose(scoreFile) == EOF)
        writeFailed = true;
    if (writeFailed)
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to write MaxScore.txt");
}

static void ReleaseResources() {
    if (MainBackGroundTexture) {
        SDL_DestroyTexture(MainBackGroundTexture);
        MainBackGroundTexture = NULL;
    }
    if (CloudTexture) {
        SDL_DestroyTexture(CloudTexture);
        CloudTexture = NULL;
    }
    if (MoonTexture) {
        SDL_DestroyTexture(MoonTexture);
        MoonTexture = NULL;
    }
    if (DinoTexture) {
        SDL_DestroyTexture(DinoTexture);
        DinoTexture = NULL;
    }
    for (int i = 0; i < GndObsVar; i++) {
        if (GndObsTexture[i]) {
            SDL_DestroyTexture(GndObsTexture[i]);
            GndObsTexture[i] = NULL;
        }
    }
    if (SkyObsTexture) {
        SDL_DestroyTexture(SkyObsTexture);
        SkyObsTexture = NULL;
    }
    if (LoseTexture) {
        SDL_DestroyTexture(LoseTexture);
        LoseTexture = NULL;
    }
    if (PauseTexture) {
        SDL_DestroyTexture(PauseTexture);
        PauseTexture = NULL;
    }
    if (BlankTexture) {
        SDL_DestroyTexture(BlankTexture);
        BlankTexture = NULL;
    }

    if (MainBackGroundSurface) {
        SDL_FreeSurface(MainBackGroundSurface);
        MainBackGroundSurface = NULL;
    }
    if (CloudSurface) {
        SDL_FreeSurface(CloudSurface);
        CloudSurface = NULL;
    }
    if (MoonSurface) {
        SDL_FreeSurface(MoonSurface);
        MoonSurface = NULL;
    }
    if (DinoSurface) {
        SDL_FreeSurface(DinoSurface);
        DinoSurface = NULL;
    }
    for (int i = 0; i < GndObsVar; i++) {
        if (GndObsSurface[i]) {
            SDL_FreeSurface(GndObsSurface[i]);
            GndObsSurface[i] = NULL;
        }
    }
    if (SkyObsSurface) {
        SDL_FreeSurface(SkyObsSurface);
        SkyObsSurface = NULL;
    }
    if (LoseSurface) {
        SDL_FreeSurface(LoseSurface);
        LoseSurface = NULL;
    }
    if (PauseSurface) {
        SDL_FreeSurface(PauseSurface);
        PauseSurface = NULL;
    }
    if (BlankSurface) {
        SDL_FreeSurface(BlankSurface);
        BlankSurface = NULL;
    }
    if (ScoreFont) {
        TTF_CloseFont(ScoreFont);
        ScoreFont = NULL;
    }
    if (Renderer) {
        SDL_DestroyRenderer(Renderer);
        Renderer = NULL;
    }
    if (Window) {
        SDL_DestroyWindow(Window);
        Window = NULL;
    }
    if (fontInitialized) {
        TTF_Quit();
        fontInitialized = false;
    }
    if (imageInitialized) {
        IMG_Quit();
        imageInitialized = false;
    }
    if (sdlInitialized) {
        SDL_Quit();
        sdlInitialized = false;
    }
    gameLoaded = false;
}

static int RunDinoGame() {
    if (!BEGIN()) {
        QUIT();
        return 1;
    }
    if (!LOAD()) {
        QUIT();
        return 1;
    }
    MainUI();
    QUIT();
    return 0;
}

int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;
    return RunDinoGame();
}

#ifdef _WIN32
int WINAPI WinMain(HINSTANCE instance, HINSTANCE previous_instance,
                   LPSTR command_line, int show_command) {
    (void)instance;
    (void)previous_instance;
    (void)command_line;
    (void)show_command;
    return RunDinoGame();
}
#endif

/********************************* The UI *********************************/
void MainUI() {
    printf("MainUI\n");
    ResetBasic();
    AllQuit = false;
    PaintAll();
    while (!AllQuit && SDL_WaitEvent(&MainEvent))
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
                    {
                        const Uint8 *keyboardState = SDL_GetKeyboardState(NULL);
                        if (!keyboardState[SDL_SCANCODE_S] &&
                            !keyboardState[SDL_SCANCODE_DOWN])
                        {
                            IsCrawl = false;
                            DinoSta = StandL;
                        }
                    }
                    break;
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
    while (SDL_WaitEvent(&MainEvent))
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

void PauseUI() {
    PaintAll();
    SDL_RenderCopy(Renderer, BlankTexture, NULL, NULL);
    SDL_RenderCopy(Renderer, PauseTexture, NULL, &BoxRect);
    SDL_RenderPresent(Renderer);
    bool PauseQuit = false;
    while (!PauseQuit && SDL_WaitEvent(&MainEvent))
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
            if (!IsCrawl && CheckSingCollision(&pObs->Sky.rect, Skydx, Skydy))
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
    if (!MenuSurface) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                     "Unable to load image/menu.png: %s", IMG_GetError());
        return;
    }
    SDL_Texture *MenuTexture = SDL_CreateTextureFromSurface(Renderer, MenuSurface);
    if (!MenuTexture) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                     "Unable to create texture for image/menu.png: %s", SDL_GetError());
        SDL_FreeSurface(MenuSurface);
        return;
    }
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

bool BEGIN() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        ReportStartupError("Unable to initialize SDL", SDL_GetError());
        SDL_Quit();
        return false;
    }
    sdlInitialized = true;

    int imageFlags = IMG_Init(IMG_INIT_PNG);
    imageInitialized = true;
    if ((imageFlags & IMG_INIT_PNG) != IMG_INIT_PNG) {
        ReportStartupError("Unable to initialize PNG support", IMG_GetError());
        return false;
    }
    if (TTF_Init() != 0) {
        ReportStartupError("Unable to initialize font support", TTF_GetError());
        return false;
    }
    fontInitialized = true;

    SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);//忽视事件处理与内存占用!!!
    Window =
        SDL_CreateWindow("DinoGame",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            wideth, height,
            SDL_WINDOW_SHOWN);
    if (!Window) {
        ReportStartupError("Unable to create the game window", SDL_GetError());
        return false;
    }
    Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
    if (!Renderer) {
        ReportStartupError("Unable to create the game renderer", SDL_GetError());
        return false;
    }
    srand((unsigned)time(NULL));
    return true;
}

// load evey needed src
bool LOAD() {
    LoadWinState();

    //this is for background
    if (!LoadSurfaceAndTexture("image/MBNG.png", &MainBackGroundSurface, &MainBackGroundTexture))
        return false;
    MainBackGroundDrect.w = MainBackGroundSrect.w = wideth;
    MainBackGroundDrect.h = MainBackGroundSrect.h = height;
    MainBackGroundSrect.y = (MainBackGroundSurface->h - height) / 2;

    if (!LoadSurface("image/BoxEnd.png", &LoseSurface)
        || !LoadSurface("image/BoxPause.png", &PauseSurface)
        || !CreateTexture("image/BoxEnd.png", LoseSurface, &LoseTexture)
        || !CreateTexture("image/BoxPause.png", PauseSurface, &PauseTexture))
        return false;
    GetDrectFromSurface(LoseSurface, &BoxRect, 1, 1, 1);
    BoxRect.x = (wideth - BoxRect.w) / 2;
    BoxRect.y = (height - BoxRect.h) / 2;

    if (!LoadSurfaceAndTexture("image/white.png", &BlankSurface, &BlankTexture))
        return false;

    ScoreFont = TTF_OpenFont("font/GenshinDefault.ttf", FontSize);
    if (!ScoreFont) {
        ReportStartupError("Unable to load the score font", TTF_GetError());
        return false;
    }

    //for borned
    BornedRect.x = wideth / 20;
    BornedRect.y = height - Horizon_dy;//左下角


    //Moon&Cloud
    if (!LoadSurfaceAndTexture("image/Moon.png", &MoonSurface, &MoonTexture))
        return false;
    GetDrectFromSurface(MoonSurface, &MoonRect, 1, 1, 1);
    MoonRect.x = rand() % (wideth - MoonRect.w);
    MoonRect.y = Sky_y - MoonRect.h;

    if (!LoadSurface("image/cloud.png", &CloudSurface)
        || !ApplyColorKey("image/cloud.png", CloudSurface, 255, 255, 255)
        || !CreateTexture("image/cloud.png", CloudSurface, &CloudTexture))
        return false;
    InitCloud();

    //Dino
    if (!LoadSurfaceAndTexture("image/dinohh.png", &DinoSurface, &DinoTexture))
        return false;
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

    if (!LoadSurface("image/Tree.png", &GndObsSurface[SingT])
        || !ApplyColorKey("image/Tree.png", GndObsSurface[SingT], 255, 255, 255)
        || !CreateTexture("image/Tree.png", GndObsSurface[SingT], &GndObsTexture[SingT])
        || !LoadSurface("image/snowman1.png", &GndObsSurface[SnowMan])
        || !ApplyColorKey("image/snowman1.png", GndObsSurface[SnowMan], 0, 0, 0)
        || !CreateTexture("image/snowman1.png", GndObsSurface[SnowMan], &GndObsTexture[SnowMan])
        || !LoadSurfaceAndTexture("image/snowball.png", &GndObsSurface[SnowBall], &GndObsTexture[SnowBall])
        || !LoadSurface("image/DoubG.png", &GndObsSurface[DoubG])
        || !ApplyColorKey("image/DoubG.png", GndObsSurface[DoubG], 255, 255, 255)
        || !CreateTexture("image/DoubG.png", GndObsSurface[DoubG], &GndObsTexture[DoubG])
        || !LoadSurfaceAndTexture("image/TribG.png", &GndObsSurface[TribG], &GndObsTexture[TribG])
        || !LoadSurface("image/Bird.png", &SkyObsSurface)
        || !ApplyColorKey("image/Bird.png", SkyObsSurface, 255, 255, 255)
        || !CreateTexture("image/Bird.png", SkyObsSurface, &SkyObsTexture))
        return false;
    GetDrectFromSurface(SkyObsSurface, &SkyObsRect_wh, 0.6, 1, 1);

    LoadMaxScore();
    gameLoaded = true;
    return true;
}

//delete all
void QUIT() {
    if (gameLoaded)
        SaveMaxScore();
    ReleaseResources();
}

