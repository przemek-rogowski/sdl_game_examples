#pragma once
#include <SDL2/SDL.h>
#include "paddle.hpp"
#include "wall.hpp"

class Ball {
private:
    bool CollidesWithRect(SDL_Rect rect);
    
public:
    int x, y;
    float velX, velY = 0.0f;
    
    Ball(int x, int y);
    
    void SetVelocity(float velX, float velY);
    
    void Update(float deltaTime);
    void Draw(SDL_Renderer* mRenderer);
    
    bool Collides(Paddle paddle);
    bool Collides(Wall wall);
    
    void BounceX();
    void BounceY();
};
