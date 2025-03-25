#include "wall.hpp"
#include <SDL2/SDL.h>


Wall::Wall(int x, int y, int w, int h): mRect(x, y, w, h) {
};

void Wall::Draw(SDL_Renderer* mRenderer) {
    SDL_RenderFillRect(mRenderer, &mRect);
};

SDL_Rect Wall::GetCollisionRect() {
    return mRect;
};
