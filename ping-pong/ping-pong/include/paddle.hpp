#pragma once
#include <SDL2/SDL.h>

class Paddle {
private:
    int mDirection = 0;
    int mScreenHeight;
    
public:
    float x, y = 0;
    
    Paddle(float x, float y, int screenHeight);
    ~Paddle() = default;
    
    void Update(float deltaTime);
    void Draw(SDL_Renderer* mRenderer);
    
    void GoUp();
    void GoDown();
    
    SDL_Rect GetCollisionRect();
};
