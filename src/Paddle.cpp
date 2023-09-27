#include "Paddle.h"

Paddle::Paddle()
{

}

Paddle::~Paddle()
{
    
}

SDL_Rect* Paddle::get_rect()
{
    return &paddle_rect;
}

void Paddle::update()
{
    SDL_GetMouseState(&mouseX, &mouseY);
    paddle_rect.x = mouseX - (paddle_rect.w / 2);
    paddle_rect.y = 600;
}