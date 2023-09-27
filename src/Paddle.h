#ifndef PADDLE_H
#define PADDLE_H

#include "Game.h"

class Paddle
{
public:
    Paddle();
    ~Paddle();
    SDL_Rect* get_rect();
    void update();
    void draw();
 
private:

    SDL_Rect paddle_rect = {800/4, 400, 32*4, 16};  // Arbitrary size atm
    int mouseX;
    int mouseY;
    
};

#endif