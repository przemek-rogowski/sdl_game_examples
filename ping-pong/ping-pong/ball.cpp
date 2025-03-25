#include "ball.hpp"
#include <SDL2/SDL.h>
#include "sdl_ext.hpp"

const int thickness = 15;
const int paddleH = 100;

Ball::Ball(int x, int y): x(x), y(y) {};

void Ball::SetVelocity(float velX, float velY) {
    this->velX = velX;
    this->velY = velY;
};

void Ball::Update(float deltaTime) {
    x += velX * deltaTime;
    y += velY * deltaTime;
};

void Ball::Draw(SDL_Renderer* mRenderer) {
    SDL_Rect ball{
        static_cast<int>(x - thickness/2),
        static_cast<int>(y - thickness/2),
        thickness,
        thickness
    };
    SDL_EXT::DrawFilledCircle(mRenderer, ball.x, ball.y, thickness/2);
};

bool Ball::CollidesWithRect(SDL_Rect rect) {
    if ((rect.x <= x && x <= (rect.x + rect.w)) && (rect.y <= y && y <= (rect.y + rect.h))) {
        return true;
    }
    return false;
}

bool Ball::Collides(Paddle paddle) {
    SDL_Rect rect = paddle.GetCollisionRect();
    return this->CollidesWithRect(rect);
};

bool Ball::Collides(Wall wall) {
    SDL_Rect rect = wall.GetCollisionRect();
    return this->CollidesWithRect(rect);
};

void Ball::BounceX() {
    velX *= -1;
};

void Ball::BounceY() {
    velY *= -1;
};

