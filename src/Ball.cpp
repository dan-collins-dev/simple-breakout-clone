#include "../include/Ball.h"
#include "../include/Paddle.h"

Ball::Ball() {}

Ball::~Ball() {}

SDL_Rect* Ball::getRect()
{
    return &ballRect;
}

void Ball::update()
{
    // Moves ball and checks if it hits walls
    // or ceiling    
    ballRect.x += xVelocity * speed;
    ballRect.y += yVelocity * speed;

    if (ballRect.x < 0)
    {
        xVelocity *= -1;
    }
    if ((ballRect.x + ballRect.w) > 600)
    {
        xVelocity *= -1;
    }
    
    if (ballRect.y < 0)
    {
        yVelocity *= -1;
    }
    if ((ballRect.y + ballRect.h) > 640)
    {
        
    }
}

void Ball::draw()
{
    SDL_SetRenderDrawColor(Game::renderer, 0, 255, 233, 255);
    SDL_RenderDrawRect(Game::renderer, &ballRect);
}

void Ball::setXVelocity(int value)
{
    xVelocity = value;
}

void Ball::setYVelocity(int value)
{
    yVelocity = value;
}