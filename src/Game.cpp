#include "../include/Game.h"
#include "../include/Paddle.h"
#include "../include/Ball.h"

SDL_Renderer *Game::renderer = nullptr;
SDL_Rect Game::gameViewPort = {0, 0, 600, 640};

Paddle *paddle = nullptr;
Ball *ball = nullptr;

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
        if (TTF_Init() == -1) {
            std::cout << "TTF Did not init" << std::endl;
        }
        else{
            std::cout << "TFF INIT" << std::endl;
            font = TTF_OpenFont("../res/windows_command_prompt.ttf", 16);
        }

        if (IMG_Init(IMG_INIT_PNG) == -1)
        {
            std::cout << "SDL_Image did not initialize." << std::endl;
            
        }
        else{
            textSurface = TTF_RenderText_Solid(font, "Testing fonts", text_color);
        }
		isRunning = true;
    }
    
    
    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    textRect = {0, 0, textSurface->w, textSurface->h};
    SDL_FreeSurface(textSurface);

    paddle = new Paddle();
    ball = new Ball();    
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
    ball->update();    
}

void Game::draw()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    

    // Draw GamePlay Stuff
    SDL_RenderSetViewport(renderer, &gameViewPort);
    SDL_RenderDrawRect(renderer, &gameViewPort);
    
    paddle->draw();
    ball->draw();
    
    // Score Viewport stuff
    SDL_RenderSetViewport(renderer, &scoreViewPort);
    SDL_SetRenderDrawColor(renderer, 240, 2, 0, 255);
    SDL_RenderFillRect(renderer, &uiRect);

    
    // Draw the font
	SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
    SDL_RenderPresent(renderer);
}

void Game::cleanup()
{
    std::cout << "Entering Game Cleanup" << std::endl;
    delete paddle;
    delete ball;
    paddle = nullptr;
    ball = nullptr;
    TTF_Quit();
    IMG_Quit();
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
}