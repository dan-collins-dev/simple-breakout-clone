#ifndef ENTITY_H
#define ENTITY_H

#include "../include/Game.h"

class Entity
{
public:
    //virtual Entity() {};
    virtual ~Entity() {};
    virtual void update() {};
    virtual void draw() {};
    virtual SDL_Rect* getRect() {};
    virtual void takeDamage() {};

private:
    SDL_Rect entityRect {0, 0, 0, 0};

};

#endif