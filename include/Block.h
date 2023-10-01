#ifndef BLOCK_H
#define BLOCK_H

#include "../include/Entity.h"

class Block : public Entity
{
public:
    Block();
    virtual ~Block();
    virtual SDL_Rect* getRect() ;
    virtual void update() ;
    virtual void draw() ;
    void takeDamage() { std::cout << "This object is damageable" << std::endl;}

private:
    SDL_Rect blockRect {800/2, 400, 32*2, 16};  // Arbitrary size atm
    int health {10};
};

#endif