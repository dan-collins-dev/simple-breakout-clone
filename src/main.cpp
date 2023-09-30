#include <iostream>
#include "../include/Game.h"

Game *game {nullptr};

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 640;

int main(int argc, char* args[])
{
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;
    
    Uint32 frameStart;
    int frameTime;

    game = new Game();
    game->initialize("Simple Breakout Clone", 800 , 640);
    
    while (game->running())
    {
        // Get current time in MS every loop
        frameStart = SDL_GetTicks();

        game->handleEvents();
        game->update();
        game->draw();

        // Work out frame time (how long it takes to handle events,
        // upates, and rendering
        frameTime = SDL_GetTicks() - frameStart;
        
        // Check to see if we need to delay rendering next frame
        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }
    
    game->cleanup();
    delete game;
    game = nullptr;

    return 0;
}