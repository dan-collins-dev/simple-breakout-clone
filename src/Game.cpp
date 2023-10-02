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
std::list<Entity*> blocks;
std::list<Entity*> killList; 

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
    
    entities.emplace_front(paddle);
    entities.emplace_front(ball);
    entities.emplace_front(block);

    blocks.emplace_front(block);


    std::cout << "List Size: " << entities.size() << std::endl;
    std::cout << "Blocks Size" << blocks.size() << std::endl;

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
    // Check for blocks flagged as hit and remove them
    if (blocks.size() > 0) {

        for (auto b : blocks) {
            if (SDL_HasIntersection(b->getRect(), ball->getRect())) {
                b->setHit(true);
                std::cout << "HIT" << std::endl;
                SDL_Rect ballRect;
                // ballRect = new SDL_Rect(ball->getRect()) ;
                SDL_Rect blockRect;
                ballRect = *ball->getRect();
                blockRect = *b->getRect();
                std::cout << "BLOCK RECT: " << blockRect.h << std::endl;
                if (ballRect.y + ballRect.h > blockRect.y) {
                    // ball->xVelocity *= -1;
                    ball->setYVelocity(-1);
                }

            

                
                killList.push_front(b);
            }

        }
    }
    
    if (SDL_HasIntersection(ball->getRect(), paddle->getRect()))
    {
        SDL_Rect ballRect;
        SDL_Rect paddleRect;

        ballRect = *ball->getRect();
        paddleRect = *paddle->getRect();

        if (ballRect.x < paddleRect.x + paddleRect.w / 2)
        {
            std::cout << "LEFT SIDE OF PADDLE HIT" << std::endl;
            std::cout << "Ball Velocity: " << ball->getXVelocity() << std::endl;

            if (ball->getXVelocity() == 1) {
                ball->setXVelocity(-1);
                std::cout << "Ball Velocity After Collision: " << ball->getXVelocity() << std::endl;
            }
            else {

                ball->setXVelocity(-1);
                std::cout << "Ball Velocity After Collision: " << ball->getXVelocity() << std::endl;
            }
        }

        if (ballRect.x >= paddleRect.x + paddleRect.w / 2)
        {
            std::cout << "RIGHT SIDE OF PADDLE HIT" << std::endl;
            std::cout << "Ball Velocity: " << ball->getXVelocity() << std::endl;
            if (ball->getXVelocity() == -1) {
                ball->setXVelocity(1);
                std::cout << "Ball Velocity After Collision: " << ball->getXVelocity() << std::endl;
            }
            else{

                ball->setXVelocity(1);
                std::cout << "Ball Velocity After Collision: " << ball->getXVelocity() << std::endl;
            }
        }
        
        if (ballRect.y + ballRect.h > paddleRect.y) {
            
            ball->setYVelocity(-1);
        }

    }

    // for (auto b : blocks) {
    //     // std::cout << "Checking for hit" << std::endl;
    //     if (b->isHit()) {
            
    //         killList.push_front(b);
    //         std::cout << "New blocks size: " << blocks.size() << std::endl;
    //     }
    // }

    // for (auto b : blocks) {
    //     if (blocks.size() > 0) {
    //         bool ranOnce {false};
    //         if(SDL_HasIntersection(b->getRect(), ball->getRect()))
    //         {
    //             if (!ranOnce) {
    //                 //blocks.remove(b);
    //                 std::cout << "RAN" << std::endl;
    //                 ranOnce = true;
    //             }
    //             else
    //             {
    //                 return;
    //             }
    //         }
    //     }
        
    // }
    for (auto e : entities) {
        e->update();
    }

    if (killList.size() > 0) {
        for (auto e : killList) {
            blocks.remove(e);
            entities.remove(e); 
        }
    }
    
    // if (blocks.empty()) {
    //     isRunning = false;
    // }
    // std::cout << "End of Game Loop" << std::endl;
    // std::cout << "Size of Blocks:" << blocks.size() << std::endl;
    // std::cout << "Size of KillList:" << killList.size() << std::endl;
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
    std::cout << blocks.size() << std::endl;
    std::cout << killList.size() << std::endl;
    delete paddle;
    delete ball;
    

    TTF_Quit();
    IMG_Quit();
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
}