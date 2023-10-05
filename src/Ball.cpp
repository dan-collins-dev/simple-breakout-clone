#include "../include/Ball.h"
#include "../include/Paddle.h"
#include <random>
#include "../include/Game.h"

Ball::Ball() {
    bounceSFX = Mix_LoadWAV("../res/ball.wav");
}

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
        Mix_PlayChannel(-1, bounceSFX, 0);
        xVelocity *= -1;
    }
    if ((ballRect.x + ballRect.w) > 600)
    {
        Mix_PlayChannel(-1, bounceSFX, 0);
        xVelocity *= -1;
    }
    
    if (ballRect.y < 0)
    {
        Mix_PlayChannel(-1, bounceSFX, 0);
        yVelocity *= -1;
    }
    if ((ballRect.y + ballRect.h) > 640)
    {
        int randomXPos = std::rand() % ((600 - ballRect.x));
        ballRect.x = randomXPos;
        ballRect.y = 400;
        //int cScore = Game::getScore();
        //Game::setScore(cScore);
        Game::currentScore -= 40;
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
