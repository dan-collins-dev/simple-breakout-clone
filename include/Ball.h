#ifndef BALL_H
#define BALL_H

#include "../include/Entity.h"

class Ball : public Entity
{
public:
    Ball();
    virtual ~Ball();
    virtual SDL_Rect* getRect();
    virtual void update();
    virtual void draw();
    void setXVelocity(int value);
    void setYVelocity(int value);
    int getXVelocity() {return xVelocity;}
    int getYVelocity() {return yVelocity;}
 
private:

    SDL_Rect ballRect {300, 0, 16, 16};  // Arbitrary size atm
    int mouseX;
    int mouseY;
    int speed {1};
    int xVelocity {1};
    int yVelocity {1};
    
};

#endif