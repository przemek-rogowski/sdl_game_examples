#include "paddle.hpp"
#include <iostream>

const int thickness = 15;
const int paddleH = 100;

Paddle::Paddle(float x, float y, int screenHeight): x(x), y(y), mScreenHeight(screenHeight) {};

void Paddle::Draw(SDL_Renderer* mRenderer) {
    SDL_Rect paddle{
        static_cast<int>(x - thickness/2),
        static_cast<int>(y - paddleH / 2.0f),
        thickness,
        paddleH
    };
    SDL_RenderFillRect(mRenderer, &paddle);
};

void Paddle::Update(float deltaTime) {
    if (mDirection != 0) {
        y += mDirection * 300.0f * deltaTime;
        
        if (y < (paddleH / 2.0f + thickness)) {
            y = paddleH / 2.0f + thickness;
        }
        if (y > (mScreenHeight - thickness - paddleH / 2.0f)) {
            y = mScreenHeight - thickness - paddleH / 2.0f;
        }
        mDirection = 0;
    }
};

void Paddle::GoUp() {
    mDirection = -1;
};

void Paddle::GoDown() {
    mDirection = 1;
};

SDL_Rect Paddle::GetCollisionRect() {
    SDL_Rect paddle{
        static_cast<int>(x - thickness/2),
        static_cast<int>(y - paddleH / 2.0f),
        thickness,
        paddleH
    };
    return paddle;
};
