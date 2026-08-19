#include "WordsAndFont.h"

TTF_Font *ScoreFont = NULL;
SDL_Color FontColor = { 83, 83, 83, 255 };// r g b a white color
SDL_Rect ScoreRect;
SDL_Rect LevelRect;

char ScoreChar[25];
char LevelChar[10];

void PaintLevel() {
    if (!ScoreFont)
        return;

    snprintf(LevelChar, sizeof(LevelChar), "Level %d", level);
    SDL_Surface *LevelSurface = TTF_RenderUTF8_Blended(ScoreFont, LevelChar, FontColor);
    if (!LevelSurface) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                     "Unable to render level text: %s", TTF_GetError());
        return;
    }
    SDL_Texture *LevelTexture = SDL_CreateTextureFromSurface(Renderer, LevelSurface);
    if (!LevelTexture) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                     "Unable to create level texture: %s", SDL_GetError());
        SDL_FreeSurface(LevelSurface);
        return;
    }
    LevelRect.h = LevelSurface->h;
    LevelRect.w = LevelSurface->w;
    LevelRect.x = 10;
    LevelRect.y = 550;
    SDL_RenderCopy(Renderer, LevelTexture, NULL, &LevelRect);
    SDL_FreeSurface(LevelSurface);
    SDL_DestroyTexture(LevelTexture);
}
void PaintScore() {
    if (!ScoreFont)
        return;

    snprintf(ScoreChar, sizeof(ScoreChar), "HI  %05.lf  %05.lf", MaxScore, Score);
    SDL_Surface *ScoreSurface = TTF_RenderUTF8_Blended(ScoreFont, ScoreChar, FontColor);
    if (!ScoreSurface) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                     "Unable to render score text: %s", TTF_GetError());
        return;
    }
    SDL_Texture *ScoreTexture = SDL_CreateTextureFromSurface(Renderer, ScoreSurface);
    if (!ScoreTexture) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                     "Unable to create score texture: %s", SDL_GetError());
        SDL_FreeSurface(ScoreSurface);
        return;
    }
    ScoreRect.w = ScoreSurface->w;
    ScoreRect.h = ScoreSurface->h;
    ScoreRect.x = wideth - 370;
    ScoreRect.y = Sky_y - 30;
    SDL_RenderCopy(Renderer, ScoreTexture, NULL, &ScoreRect);
    SDL_FreeSurface(ScoreSurface);
    SDL_DestroyTexture(ScoreTexture);
}
