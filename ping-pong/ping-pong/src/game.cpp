#include "game.hpp"
#include <iostream>

const int thickness = 15;

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

Game::Game(): mWindow(nullptr), mRenderer(nullptr), mIsRunning(true),
    mLeftPaddle(thickness*2, SCREEN_HEIGHT/2, SCREEN_HEIGHT),
    mRightPaddle(SCREEN_WIDTH - thickness, SCREEN_HEIGHT/2, SCREEN_HEIGHT),
    mBall({SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2}),
    mUpperWall(0, 0, SCREEN_WIDTH, thickness),
    mLowerWall(0, SCREEN_HEIGHT - thickness, SCREEN_WIDTH, thickness) {}

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
    
    mBall.SetVelocity(-200.0f, 235.0f);
    
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
        mLeftPaddle.GoUp();
    }
    if (state[SDL_SCANCODE_S]) {
        mLeftPaddle.GoDown();
    }
    
    if (state[SDL_SCANCODE_I]) {
        mRightPaddle.GoUp();
    }
    if (state[SDL_SCANCODE_K]) {
        mRightPaddle.GoDown();
    }
}


void Game::UpdateGame() {
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount+16));
    
    float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
    mTicksCount = SDL_GetTicks();
    
    if (deltaTime > 0.5f) {
        deltaTime = 0.5f;
    }
    
    mLeftPaddle.Update(deltaTime);
    mRightPaddle.Update(deltaTime);
    mBall.Update(deltaTime);
    
    if (mBall.Collides(mLeftPaddle) || mBall.Collides(mRightPaddle)) {
        mBall.BounceX();
    } else if (mBall.x < 0.0f || SCREEN_WIDTH < mBall.x) {
        mIsRunning = false;
    } else if (mBall.Collides(mUpperWall) || mBall.Collides(mLowerWall)) {
        mBall.BounceY();
    }
}

void Game::GenerateOutput() {
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 255, 255);
    SDL_RenderClear(mRenderer);
    
    SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
    
    mUpperWall.Draw(mRenderer);
    mLowerWall.Draw(mRenderer);
    
    mLeftPaddle.Draw(mRenderer);
    mRightPaddle.Draw(mRenderer);
    
    mBall.Draw(mRenderer);
    
    SDL_RenderPresent(mRenderer);
}
