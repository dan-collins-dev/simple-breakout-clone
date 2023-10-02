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
    virtual bool isHit() {return hit;}
    virtual void setHit(bool value) {hit = value;}
    virtual void setYVelocity(int value) {};
    virtual void setXVelocity(int value) {};
    virtual int getYVelocity() {};
    virtual int getXVelocity() {};

private:
    SDL_Rect entityRect {0, 0, 0, 0};
    bool hit {false};
    //int xVelocity {0};

};

#endif