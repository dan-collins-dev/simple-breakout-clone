#include "../include/Ball.h"

Ball::Ball()
{

}

Ball::~Ball()
{
    
}

SDL_Rect* Ball::get_rect()
{
    return &ball_rect;
}

void Ball::update()
{
    SDL_GetMouseState(&mouseX, &mouseY);
    
    ball_rect.x = mouseX - (ball_rect.w / 2);
    ball_rect.y = mouseY;
    
}

void Ball::draw()
{
    SDL_SetRenderDrawColor(Game::renderer, 0, 255, 233, 255);
    SDL_RenderDrawRect(Game::renderer, &ball_rect);
}