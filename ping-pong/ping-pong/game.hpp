#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

struct Vector2 {
    float x, y;
};

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
    
    Uint32 mTicksCount = 0;

    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    bool mIsRunning;
    
    Vector2 mPaddlePos;
    Vector2 mBallPos;
    
    Vector2 mBallVel;
    
    int mPaddleDir = 0;
};

