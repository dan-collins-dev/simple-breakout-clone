#include "../include/Paddle.h"

Paddle::Paddle() {}

Paddle::~Paddle() {}

SDL_Rect* Paddle::get_rect()
{
    return &paddle_rect;
}

void Paddle::update()
{
    SDL_GetMouseState(&mouseX, &mouseY);
    
    paddle_rect.x = mouseX - (paddle_rect.w / 2);
    
    if (paddle_rect.x < 1)
    {
        paddle_rect.x = 1;
    }
    
    if (paddle_rect.x + paddle_rect.w > Game::gameViewPort.x + Game::gameViewPort.w) {
        paddle_rect.x = Game::gameViewPort.x + Game::gameViewPort.w - paddle_rect.w - 1;
    }
    
    paddle_rect.y = 600;
}

void Paddle::draw()
{
    SDL_SetRenderDrawColor(Game::renderer, 0, 255, 0, 255);
    SDL_RenderDrawRect(Game::renderer, &paddle_rect);
}