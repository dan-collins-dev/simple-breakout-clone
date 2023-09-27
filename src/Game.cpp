#include "Game.h"
#include "Paddle.h"

SDL_Renderer *Game::renderer = nullptr;

Paddle *paddle = nullptr;

Game::Game()
{
    
}

Game::~Game()
{
    
}

void Game::initialize(const char* window_title, int width, int height)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout << "Initialized" << std::endl;
        window = SDL_CreateWindow("Simple Breakout Clone",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            width, height, SDL_WINDOW_SHOWN);
            
        renderer = SDL_CreateRenderer(window, -1, 0);
        
        SDL_ShowCursor(SDL_DISABLE);
        SDL_SetRelativeMouseMode(SDL_TRUE);
        
        if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		}
		isRunning = true;
    }
    
    paddle = new Paddle();
}

void Game::handleEvents()
{
    SDL_Event e;
    SDL_PollEvent(&e);
    
    if (e.type == SDL_QUIT)
    {
        isRunning = false;
    }
    else if (e.type == SDL_KEYDOWN) 
    {
        if (e.key.keysym.sym == SDLK_ESCAPE)
        {
            SDL_ShowCursor(SDL_ENABLE);
            SDL_SetRelativeMouseMode(SDL_FALSE);
        }
    }
}

void Game::update()
{
    paddle->update();
}

void Game::draw()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    
    paddle->draw();
    
	SDL_RenderPresent(renderer);
}

void Game::cleanup()
{
    std::cout << "Entering Game Cleanup" << std::endl;
    delete paddle;
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
}