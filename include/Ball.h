#ifndef BALL_H
#define BALL_H

#include "../include/Game.h"

class Ball
{
public:
    Ball();
    ~Ball();
    SDL_Rect* get_rect();
    void update();
    void draw();
 
private:

    SDL_Rect ball_rect = {800/4, 400, 16, 16};  // Arbitrary size atm
    int mouseX;
    int mouseY;
    
};

#endif