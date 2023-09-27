#include <iostream>
//#include <SDL2/SDL.h>
//#include <SDL2/SDL_image.h>
//#include <SDL2/SDL_ttf.h>
//#include <SDL2/SDL_mixer.h>
//#include <SDL2/SDL_mouse.h>

#include "Paddle.h"
#include "Game.h"

Game *game = nullptr;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 640;

int main(int argc, char* args[])
{
    game = new Game();
    game->initialize("Simple Breakout Clone", 800 , 640);
    
    while (game->running())
    {
        game->handleEvents();
        game->update();
        game->draw();
    }
    
    game->cleanup();

    return 0;
}