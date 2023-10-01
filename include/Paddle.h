#ifndef PADDLE_H
#define PADDLE_H

#include "../include/Entity.h"

class Paddle : public Entity
{
public:
    Paddle();
    ~Paddle();
    virtual SDL_Rect* getRect();
    virtual void update();
    virtual void draw();
 
private:

    SDL_Rect paddleRect = {800/4, 400, 32*4, 16};  // Arbitrary size atm
    int mouseX;
    int mouseY;
    
};

#endif