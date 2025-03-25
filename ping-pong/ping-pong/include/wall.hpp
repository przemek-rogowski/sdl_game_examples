#pragma once
#include <SDL2/SDL.h>

class Wall {
private:
    //int x, y, w, h;
    SDL_Rect mRect;
public:
    Wall(int x, int y, int w, int h);
    
    void Draw(SDL_Renderer* mRenderer);
    
    SDL_Rect GetCollisionRect();
};
