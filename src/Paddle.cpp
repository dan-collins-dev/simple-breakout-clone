#include "Paddle.h"

Paddle::Paddle()
{

}

Paddle::~Paddle()
{
    
}

SDL_Rect* Paddle::get_rect()
{
    std::cout << "From get rect" << std::endl;
    return &paddle_rect;
}

void Paddle::update()
{
    SDL_GetMouseState(&mouseX, &mouseY);
    
    paddle_rect.x = mouseX - (paddle_rect.w / 2);
    
    if (paddle_rect.x < 0)
    {
        paddle_rect.x = 0;
    }
    
    if (paddle_rect.x + paddle_rect.w > 800) {
        paddle_rect.x = 800 - paddle_rect.w;
    }
    
    paddle_rect.y = 600;
}

void Paddle::draw()
{
    SDL_SetRenderDrawColor(Game::renderer, 0, 255, 0, 255);
    SDL_RenderDrawRect(Game::renderer, &paddle_rect);
}