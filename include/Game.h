#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>

class Game
{
public:
    Game();
    ~Game();
    void initialize(const char* window_title, int width, int height);
    void handleEvents();
    void update();
    void draw();
    void cleanup();
    bool running() {return isRunning;}
    static SDL_Renderer *renderer;
    static SDL_Rect gameViewPort;
    SDL_Rect scoreViewPort {601, 0, 200, 640};
    SDL_Rect uiRect {0, 0, 200, 640};
    
private:
    bool isRunning = false;
    SDL_Window *window;
    TTF_Font *font;
    SDL_Color text_color = {0, 0, 0};
    SDL_Surface* textSurface;
    SDL_Texture* textTexture;
    SDL_Rect textRect;
};

#endif