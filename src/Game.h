#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
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
    
private:
    bool isRunning = false;
    SDL_Window *window;
};

#endif