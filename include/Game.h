#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <list>
//#include "../include/Block.h"
//#include "../include/Entity.h"

class Game
{
public:
    Game();
    ~Game();
    void initialize(const char* windowTitle, int width, int height);
    void handleEvents();
    void update();
    void draw();
    void cleanup();
    bool running() {return isRunning;}
    void handleCollisions();
    static SDL_Renderer *renderer;
    static SDL_Rect gameViewPort;
    SDL_Rect scoreViewPort {600, 0, 200, 640};
    SDL_Rect uiRect {0, 0, 200, 640};
    
    
private:
    bool isRunning = false;
    SDL_Window *window;
    TTF_Font *font;
    SDL_Color textColor {18, 206, 106};
    SDL_Surface* textSurface;
    SDL_Texture* textTexture;
    SDL_Rect textRect;
};

#endif