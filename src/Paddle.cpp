#include "../include/Paddle.h"

Paddle::Paddle() {}

Paddle::~Paddle() {}

SDL_Rect* Paddle::getRect()
{
    return &paddleRect;
}

void Paddle::update()
{
    SDL_GetMouseState(&mouseX, &mouseY);
    
    paddleRect.x = mouseX - (paddleRect.w / 2);
    
    if (paddleRect.x < 1)
    {
        paddleRect.x = 1;
    }
    
    if (paddleRect.x + paddleRect.w > Game::gameViewPort.x + Game::gameViewPort.w) {
        paddleRect.x = Game::gameViewPort.x + Game::gameViewPort.w - paddleRect.w - 1;
    }
    
    paddleRect.y = 600;
}

void Paddle::draw()
{
    SDL_SetRenderDrawColor(Game::renderer, 0, 255, 0, 255);
    SDL_RenderDrawRect(Game::renderer, &paddleRect);
}