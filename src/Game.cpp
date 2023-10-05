#include "../include/Game.h"
#include "../include/Paddle.h"
#include "../include/Ball.h"
#include "../include/Block.h"
#include "../include/Entity.h"
#include "../include/FontManager.h"
#include <cstdio>

SDL_Renderer *Game::renderer {nullptr};
SDL_Rect Game::gameViewPort {0, 0, 600, 640};

int Game::currentScore = 0;

Entity *paddle {nullptr};
Entity *ball {nullptr};

FontManager *GameFont {nullptr};

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
            
        }

        if (IMG_Init(IMG_INIT_PNG) == -1)
        {
            std::cout << "SDL_Image did not initialize." << std::endl;
            
        }
        else{
            
        }
		isRunning = true;
    }
    
    
    
    //Create Stats Label
    font = TTF_OpenFont("../res/windows_command_prompt.ttf", 32);
    textSurface = TTF_RenderText_Solid(font, "Stats", textColor);
    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    textRect = {0, 0, textSurface->w, textSurface->h};
    textRect.x = uiRect.w / 3;
    SDL_FreeSurface(textSurface);
    TTF_CloseFont(font);

    
    // GameFont = new FontManager();
    // FontData *statFontData {nullptr};
    // std::cout << "Crash afteer creating ptr"  << std::endl;
    // statFontData = GameFont->createFontData("../res/windows_command_prompt.ttf", 32, textColor);
    // std::cout << "STAT FONT DATA RECT X" << statFontData->rect.x << std::endl;
    // //GameFont->cleanUp();
    

    
    

    // Create Score Label
    scoreFont = TTF_OpenFont("../res/windows_command_prompt.ttf", 16);
    scoreSurface = TTF_RenderText_Solid(scoreFont, "Score" , textColor);
    scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
    scoreRect = {0, 0, scoreSurface->w, scoreSurface->h};
    scoreRect.x = uiRect.w / 16;
    scoreRect.y = 40;
    SDL_FreeSurface(scoreSurface);
    TTF_CloseFont(scoreFont);
    Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 );
    // // Example of coverting string to const char*
    // std::string scoreValue = std::to_string(currentScore);
    // const char *scoreValueString = scoreValue.c_str();

    // // Create Score Value Label (Updated when score increases)
    // scoreValueFont = TTF_OpenFont("../res/windows_command_prompt.ttf", 16);
    // scoreValueSurface = TTF_RenderText_Solid(scoreValueFont, scoreValueString , textColor);
    // scoreValueTexture = SDL_CreateTextureFromSurface(renderer, scoreValueSurface);
    // scoreValueRect = {0, 0, scoreValueSurface->w, scoreValueSurface->h};
    // scoreValueRect.x = uiRect.w / 2;
    // scoreValueRect.y = 40;
    // SDL_FreeSurface(scoreValueSurface);
    // TTF_CloseFont(scoreValueFont);
    
    blockDestroySFX = Mix_LoadWAV("../res/blockDestruction.wav");
    paddleSFX = Mix_LoadWAV("../res/paddleSFX.wav");


    paddle = new Paddle();
    ball = new Ball();


    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 5; y++) {
            Block *b {nullptr};
            b = new Block(x * 64 + 40, y * 16 + 32, 64, 16);
            blocks.emplace_front(b);
            entities.emplace_front(b);
            b = nullptr;
            delete b;
        }
    }
    
    entities.emplace_front(paddle);
    entities.emplace_front(ball);

    std::cout << "Entity List Size: " << entities.size() << std::endl;
    std::cout << "Blocks List Size: " << blocks.size() << std::endl;
    std::cout << "Kill List Size: " << killList.size() << std::endl;
}

void Game::handleEvents()
{
    SDL_Event e;
    SDL_PollEvent(&e);
    
    if (e.type == SDL_QUIT)
    {
        isRunning = false;
    }
    

    const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
    if( currentKeyStates[ SDL_SCANCODE_ESCAPE ] )
    {
        SDL_ShowCursor(SDL_ENABLE);
            SDL_SetRelativeMouseMode(SDL_FALSE);
    }
}

void Game::update() {
    handleBlockCollisions();
    handlePaddleCollisions();

    for (auto e : entities) {
        e->update();
    }

    if (killList.size() > 0) {
        for (auto e : killList) {
            blocks.remove(e);
            entities.remove(e); 
        }
    }
    
    if (blocks.empty()) {
        isRunning = false;
    }
    std::cout << "End of Game Loop" << std::endl;
    std::cout << "Size of Blocks:" << blocks.size() << std::endl;
    std::cout << "Size of KillList:" << killList.size() << std::endl;
}

void Game::draw() {
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

    // Example of coverting string to const char*
    std::string scoreValue = std::to_string(currentScore);
    const char *scoreValueString = scoreValue.c_str();

    // Create Score Value Label (Updated when score increases)
    scoreValueFont = TTF_OpenFont("../res/windows_command_prompt.ttf", 16);
    scoreValueSurface = TTF_RenderText_Solid(scoreValueFont, scoreValueString , textColor);
    scoreValueTexture = SDL_CreateTextureFromSurface(renderer, scoreValueSurface);
    scoreValueRect = {0, 0, scoreValueSurface->w, scoreValueSurface->h};
    scoreValueRect.x = uiRect.w / 2 + uiRect.w / 3;
    scoreValueRect.y = 40;
    SDL_FreeSurface(scoreValueSurface);
    TTF_CloseFont(scoreValueFont);
    
	SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
    SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);
    SDL_RenderCopy(renderer, scoreValueTexture, NULL, &scoreValueRect);

    //FontData newFont = *GameFont->createFontData("../res/windows_command_prompt.ttf", 64, textColor);

    //SDL_RenderCopy(renderer, newFont.texture, NULL, &newFont.rect);

    //GameFont->cleanUp();

    SDL_RenderPresent(renderer);
}

void Game::cleanup() {
    std::cout << "Entering Game Cleanup" << std::endl;
    std::cout << blocks.size() << std::endl;
    std::cout << killList.size() << std::endl;
    delete paddle;
    delete ball;
    

    TTF_Quit();
    IMG_Quit();

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

void Game::handlePaddleCollisions() {
    
    if (SDL_HasIntersection(ball->getRect(), paddle->getRect()))
    {
        Mix_PlayChannel(-1, paddleSFX, 0);
        //paddle->setHit(true);
        SDL_Rect ballRect;
        SDL_Rect paddleRect;

        ballRect = *ball->getRect();
        paddleRect = *paddle->getRect();

        if (ballRect.x < paddleRect.x + paddleRect.w / 2) {
            //std::cout << "LEFT SIDE OF PADDLE HIT" << std::endl;
            //std::cout << "Ball Velocity: " << ball->getXVelocity() << std::endl;

            if (ball->getXVelocity() == 1) {
                ball->setXVelocity(-1);
                //std::cout << "Ball Velocity After Collision: " << ball->getXVelocity() << std::endl;
            }
            else {
                ball->setXVelocity(-1);
                //std::cout << "Ball Velocity After Collision: " << ball->getXVelocity() << std::endl;
            }  
        }

        if (ballRect.x >= paddleRect.x + paddleRect.w / 2) {
            //std::cout << "RIGHT SIDE OF PADDLE HIT" << std::endl;
            //std::cout << "Ball Velocity: " << ball->getXVelocity() << std::endl;
            if (ball->getXVelocity() == -1) {
                ball->setXVelocity(1);
                //std::cout << "Ball Velocity After Collision: " << ball->getXVelocity() << std::endl;
            }
            else {
                ball->setXVelocity(1);
                //std::cout << "Ball Velocity After Collision: " << ball->getXVelocity() << std::endl;
            }
        }
        
        ball->setYVelocity(-1);
    }
}

void Game::handleBlockCollisions() {
    if (blocks.size() > 0) {

        for (auto b : blocks) {

            if (SDL_HasIntersection(b->getRect(), ball->getRect())) {
                Mix_PlayChannel(-1, blockDestroySFX, 0);
                currentScore += 100;
                b->setHit(true);
                SDL_Rect ballRect;
                SDL_Rect blockRect;
                ballRect = *ball->getRect();
                blockRect = *b->getRect();

                if (ballRect.y + ballRect.h > blockRect.y) {
                    int newDirection = ball->getYVelocity() * -1;
                    ball->setYVelocity(newDirection);
                }
                else if (ballRect.y > blockRect.y + blockRect.h) {
                    int newDirection = ball->getYVelocity() * -1;
                    ball->setYVelocity(newDirection);
                }

                if (ballRect.x < blockRect.x + blockRect.w / 2) {
                    //std::cout << "LEFT SIDE OF BLOCK HIT" << std::endl;
                    //std::cout << "Ball Velocity: " << ball->getXVelocity() << std::endl;
                
                    if (ball->getXVelocity() == 1) {
                        ball->setXVelocity(-1);
                        //std::cout << "Ball Velocity After Collision: " << ball->getXVelocity() << std::endl;
                    }
                    else {

                        ball->setXVelocity(-1);
                        //std::cout << "Ball Velocity After Collision: " << ball->getXVelocity() << std::endl;
                    }
                }

                if (ballRect.x >= blockRect.x + blockRect.w / 2) {
                    //std::cout << "RIGHT SIDE OF BLOCK HIT" << std::endl;
                    //std::cout << "Ball Velocity: " << ball->getXVelocity() << std::endl;
                    if (ball->getXVelocity() == -1) {
                        ball->setXVelocity(1);
                        //std::cout << "Ball Velocity After Collision: " << ball->getXVelocity() << std::endl;
                    }
                    else {
                        ball->setXVelocity(1);
                        //std::cout << "Ball Velocity After Collision: " << ball->getXVelocity() << std::endl;
                    }
                }

                killList.push_front(b);
            }
        }
    }
}