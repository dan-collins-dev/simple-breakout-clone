#include "../include/Game.h"
#include "../include/Paddle.h"
#include "../include/Ball.h"
#include "../include/Block.h"
#include "../include/Entity.h"

SDL_Renderer *Game::renderer {nullptr};
SDL_Rect Game::gameViewPort {0, 0, 600, 640};

Entity *paddle {nullptr};
Entity *ball {nullptr};
Entity *block {nullptr};
Entity *block2 {nullptr};

std::list<Entity*> entities;
std::list<Block*> blocks;

Game::Game() {}

Game::~Game() {}

void Game::initialize(const char* windowTitle, int width, int height)
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
            textSurface = TTF_RenderText_Solid(font, "Testing fonts", textColor);
        }
		isRunning = true;
    }
    
    
    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    textRect = {0, 0, textSurface->w, textSurface->h};
    SDL_FreeSurface(textSurface);

    paddle = new Paddle();
    ball = new Ball();

    

    block = new Block();
    block2 = new Block();


    entities.emplace_front(block2);
    entities.emplace_front(paddle);
    entities.emplace_front(ball);
    entities.emplace_front(block);


    std::cout << "List Size: " << entities.size() << std::endl;
    for (auto e : entities) {
        // if (dynamic_cast<Entity*>) 
        // {
        //     std::cout << "This is a block" << std::endl;
        // }
        e->takeDamage();
    }

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
    for (auto e : entities) {
        e->update();
    }   
}

void Game::draw()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    

    // Draw GamePlay Stuff
    SDL_RenderSetViewport(renderer, &gameViewPort);
    SDL_SetRenderDrawColor(renderer, 18, 206, 106, 255);
    SDL_RenderDrawRect(renderer, &gameViewPort);
    
    for (auto e : entities) {
        e->draw();
    }
    
    // Score Viewport stuff
    SDL_RenderSetViewport(renderer, &scoreViewPort);
    SDL_RenderDrawRect(renderer, &uiRect);

    
    // Draw the font
	SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
    SDL_RenderPresent(renderer);
}

void Game::cleanup()
{
    std::cout << "Entering Game Cleanup" << std::endl;
    delete paddle;
    delete ball;

    TTF_Quit();
    IMG_Quit();
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
}