#include "../include/Block.h"


Block::Block() {}

Block::Block(int startXPos, int startYPos, int w, int h) {
    blockRect = {startXPos, startYPos, w, h};
}

Block::~Block() {}

SDL_Rect* Block::getRect() {
    return &blockRect;
}

void Block::update() {

}

void Block::draw() {
    SDL_SetRenderDrawColor(Game::renderer, 255, 0, 0, 255);
    SDL_RenderDrawRect(Game::renderer, &blockRect);
}