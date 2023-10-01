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
    // Check for collisions
    // If a block:
    //  Reflect based on where the ball hit the block
    //  Remove block from block list and free it

    // If paddle:
    //  Reflect based on where the ball hit the paddle


    // SDL_GetMouseState(&mouseX, &mouseY);
    
    // ballRect.x = mouseX - (ballRect.w / 2);
    // ballRect.y = mouseY;

    ballRect.x -= xVelocity;
    ballRect.y -= yVelocity;

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
        yVelocity *= -1;
    
    }
}

void Ball::draw()
{
    SDL_SetRenderDrawColor(Game::renderer, 0, 255, 233, 255);
    SDL_RenderDrawRect(Game::renderer, &ballRect);
}