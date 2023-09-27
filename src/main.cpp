#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_mouse.h>
#include "Paddle.h"

int main(int argc, char* args[])
{
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    bool isRunning = true;
    SDL_Event e;
    
    Paddle *paddle = nullptr;
    paddle = new Paddle();
    
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        window = SDL_CreateWindow("Simple Breakout Clone", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(window, -1, 0);
        
        while (isRunning) 
        {
            SDL_PollEvent(&e);
            // Get Input
            if (e.type == SDL_QUIT)
            {
                isRunning = false;
            }
        
            // Update
            paddle->update();
            
            
            // Draw
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            SDL_RenderDrawRect(renderer, paddle->get_rect());
            SDL_RenderPresent(renderer);
            
            
        }
    }
    
    delete paddle;
    
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
}