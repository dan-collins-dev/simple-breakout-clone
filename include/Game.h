#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <list>
#include "../include/FontManager.h"
//#include "../include/Block.h"
//#include "../include/Entity.h"

class Game {
public:
    Game();
    ~Game();
    void initialize(const char* windowTitle, int width, int height);
    void handleEvents();
    void update();
    void draw();
    void cleanup();
    bool running() {return isRunning;}
    static SDL_Renderer *renderer;
    static SDL_Rect gameViewPort;
    void handlePaddleCollisions();
    void handleBlockCollisions();
    // int getScore() {return score;}
    // void setScore(int value)
    SDL_Rect scoreViewPort {600, 0, 200, 640};
    SDL_Rect uiRect {0, 0, 200, 640};
    
    
private:
    bool isRunning = false;
    SDL_Window *window;

    //Stats Label
    TTF_Font *font;
    SDL_Color textColor {18, 206, 106};
    SDL_Surface* textSurface;
    SDL_Texture* textTexture;
    SDL_Rect textRect;

    //Score Label
    TTF_Font *scoreFont;
    SDL_Surface* scoreSurface;
    SDL_Texture* scoreTexture;
    SDL_Rect scoreRect;

    //Score Value Label
    TTF_Font *scoreValueFont;
    SDL_Surface* scoreValueSurface;
    SDL_Texture* scoreValueTexture;
    SDL_Rect scoreValueRect;


    int currentScore {0};
    int previousScore {0};
};

#endif