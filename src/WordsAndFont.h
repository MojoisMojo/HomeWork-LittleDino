#ifndef WORDSANDFONT_H
#define WORDSANDFONT_H

#define FontSize 36
TTF_Font *ScoreFont = NULL;
SDL_Color FontColor = { 83, 83, 83, 255 };// r g b a white color
SDL_Rect ScoreRect;
SDL_Rect LevelRect;

char ScoreChar[25];
char LevelChar[10];

void PaintLevel();
void PaintScore();

void PaintLevel() {
    sprintf(LevelChar, "Level %d", level);
    SDL_Surface *LevelSurface = TTF_RenderUTF8_Blended(ScoreFont, LevelChar, FontColor);
    SDL_Texture *LevelTexture = SDL_CreateTextureFromSurface(Renderer, LevelSurface);
    LevelRect.h = LevelSurface->h;
    LevelRect.w = LevelSurface->w;
    LevelRect.x = 10;
    LevelRect.y = 550;
    SDL_RenderCopy(Renderer, LevelTexture, NULL, &LevelRect);
    SDL_FreeSurface(LevelSurface);
    SDL_DestroyTexture(LevelTexture);
}
void PaintScore() {
    sprintf(ScoreChar, "HI  %05.lf  %05.lf", MaxScore, Score);
    SDL_Surface *ScoreSurface = TTF_RenderUTF8_Blended(ScoreFont, ScoreChar, FontColor);
    SDL_Texture *ScoreTexture = SDL_CreateTextureFromSurface(Renderer, ScoreSurface);
    ScoreRect.w = ScoreSurface->w;
    ScoreRect.h = ScoreSurface->h;
    ScoreRect.x = wideth - 370;
    ScoreRect.y = Sky_y - 30;
    SDL_RenderCopy(Renderer, ScoreTexture, NULL, &ScoreRect);
    SDL_FreeSurface(ScoreSurface);
    SDL_DestroyTexture(ScoreTexture);
}
#endif