#pragma once
#include <SDL2/SDL.h>
#include "paddle.hpp"
#include "ball.hpp"
#include "wall.hpp"

class Game {
public:
    Game();
    bool Initialize();
    void RunLoop();
    void Shutdown();
    
private:
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();
    
    Paddle mLeftPaddle;
    Paddle mRightPaddle;
    Ball mBall;
    
    Wall mUpperWall;
    Wall mLowerWall;
    
    Uint32 mTicksCount = 0;

    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    bool mIsRunning;
};

