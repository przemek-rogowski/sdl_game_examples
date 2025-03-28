#pragma once
#include <SDL2/SDL.h>

class Game {
public:
    Game();
    ~Game() = default;
    bool Initialize();
    void RunLoop();
    void Shutdown();
    
private:
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();
    
};
