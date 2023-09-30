#include "../include/Ball.h"

Ball::Ball() {}

Ball::~Ball() {}

SDL_Rect* Ball::get_rect()
{
    return &ball_rect;
}

void Ball::update()
{
    SDL_GetMouseState(&mouseX, &mouseY);
    
    ball_rect.x = mouseX - (ball_rect.w / 2);
    ball_rect.y = mouseY;

    // ball_rect.x -= xVelocity;
    // ball_rect.y -= yVelocity;

    // if (ball_rect.x < 0)
    // {
    //     xVelocity *= -1;
    // }
    // if ((ball_rect.x + ball_rect.w) > 800)
    // {
    //     xVelocity *= -1;
    // }
    
}

void Ball::draw()
{
    SDL_SetRenderDrawColor(Game::renderer, 0, 255, 233, 255);
    SDL_RenderDrawRect(Game::renderer, &ball_rect);
}