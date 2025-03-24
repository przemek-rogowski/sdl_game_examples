#include "game.hpp"
#include <iostream>
#include "sdl_ext.hpp"
#include <cstdlib>

const int thickness = 15;
const int paddleH = 100;

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

Game::Game(): mWindow(nullptr), mRenderer(nullptr), mIsRunning(true) {
}

bool Game::Initialize() {
    
    int sdl_result = SDL_Init(SDL_INIT_VIDEO);
    if (sdl_result != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }
    
    mWindow = SDL_CreateWindow(
                                "Ping Pong",
                                SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED,
                                SCREEN_WIDTH,
                                SCREEN_HEIGHT,
                                SDL_WINDOW_SHOWN
                                );
    if (!mWindow) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }
    
    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!mRenderer) {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return false;
    }
    
    mPaddlePos = {thickness*2, SCREEN_HEIGHT/2};
    mBallPos = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
    mBallVel = {-200.0f, 235.0f};
    
    return true;
}

void Game::Shutdown() {
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

void Game::RunLoop() {
    while (mIsRunning) {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

void Game::ProcessInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                mIsRunning = false;
                break;
        }
    }
    
    const Uint8* state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_ESCAPE]) {
        mIsRunning = false;
    }
    
    if (state[SDL_SCANCODE_W]) {
        mPaddleDir = -1;
    }
    if (state[SDL_SCANCODE_S]) {
        mPaddleDir = 1;
    }
}


void Game::UpdateGame() {
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount+16));
    
    float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
    mTicksCount = SDL_GetTicks();
    
    if (deltaTime > 0.5f) {
        deltaTime = 0.5f;
    }
    
    if (mPaddleDir != 0) {
        mPaddlePos.y += mPaddleDir * 300.0f * deltaTime;
        
        if (mPaddlePos.y < (paddleH / 2.0f + thickness)) {
            mPaddlePos.y = paddleH / 2.0f + thickness;
        }
        if (mPaddlePos.y > (SCREEN_HEIGHT - thickness - paddleH / 2.0f)) {
            mPaddlePos.y = SCREEN_HEIGHT - thickness - paddleH / 2.0f;
        }
    }
    
    mBallPos.x += mBallVel.x * deltaTime;
    mBallPos.y += mBallVel.y * deltaTime;
    
    float diff = abs(mPaddlePos.y - mBallPos.y);
    
    if (
        diff <= paddleH / 2.0f &&
        mBallPos.x <= (mPaddlePos.x + thickness) &&
        (mPaddlePos.x - thickness) <= mBallPos.x &&
        mBallVel.x < 0.0f
        )
    {
        mBallVel.x *= -1.0f;
    } else if (mBallPos.x < 0.0f) {
        mIsRunning = false;
    } else if (mBallPos.y <= 1.5*thickness && mBallVel.y < 0.0f) {
        mBallVel.y *= -1;
    } else if (mBallPos.y >= SCREEN_HEIGHT - thickness) {
        mBallVel.y = -mBallVel.y;
    } else if (mBallPos.x >= SCREEN_WIDTH - thickness) {
        mBallVel.x = -mBallVel.x;
    }
}

void Game::GenerateOutput() {
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 255, 255);
    SDL_RenderClear(mRenderer);
    
    SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
    SDL_Rect upperWall {0, 0, SCREEN_WIDTH, thickness};
    SDL_RenderFillRect(mRenderer, &upperWall);
    
    SDL_Rect downWall {0, SCREEN_HEIGHT - thickness, SCREEN_WIDTH, thickness};
    SDL_RenderFillRect(mRenderer, &downWall);
    
    SDL_Rect rightWall {SCREEN_WIDTH - thickness, 0, thickness, SCREEN_HEIGHT};
    SDL_RenderFillRect(mRenderer, &rightWall);
    
    SDL_Rect ball{
        static_cast<int>(mBallPos.x - thickness/2),
        static_cast<int>(mBallPos.y - thickness/2),
        thickness,
        thickness
    };
    SDL_EXT::DrawFilledCircle(mRenderer, ball.x, ball.y, thickness/2);
    
    SDL_Rect paddle{
        static_cast<int>(mPaddlePos.x - thickness/2),
        static_cast<int>(mPaddlePos.y - paddleH / 2.0f),
        thickness,
        paddleH
    };
    SDL_RenderFillRect(mRenderer, &paddle);
    
    SDL_RenderPresent(mRenderer);
}
