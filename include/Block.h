#ifndef BLOCK_H
#define BLOCK_H

#include "../include/Entity.h"

class Block : public Entity
{
public:
    Block();
    Block(int startXPos, int startYPos, int width, int height);
    virtual ~Block();
    virtual SDL_Rect* getRect();
    virtual void update() ;
    virtual void draw() ;
    virtual void setHit(bool value) {hit = value;}

private:
    SDL_Rect blockRect {800/2, 400, 32*2, 16};  // Arbitrary size atm
    bool hit {false};
};

#endif