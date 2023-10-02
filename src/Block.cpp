#include "../include/Block.h"


Block::Block() {}

Block::~Block() {}

SDL_Rect* Block::getRect()
{
    return &blockRect;
}

void Block::update()
{
    if (hit) {
        
    }
    
}

void Block::draw()
{
    SDL_SetRenderDrawColor(Game::renderer, 255, 0, 0, 255);
    SDL_RenderDrawRect(Game::renderer, &blockRect);
}