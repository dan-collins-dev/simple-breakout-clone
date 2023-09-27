#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>


int main(int argc, char* args[])
{
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    bool isRunning = true;
    SDL_Event e;
    SDL_Rect paddle = {800/4, 640/3, 32*4, 16};
    
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        window = SDL_CreateWindow("Breakout", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, SDL_WINDOW_SHOWN);
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
            // Draw
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            
            SDL_SetRenderDrawColor( renderer, 0, 255, 0, 255 );
            SDL_RenderDrawRect(renderer, &paddle);
            SDL_RenderPresent(renderer);
            
            
        }
    }
    
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
}
