#include <SDL2/SDL.h>
#include <iostream>
#include "game.hpp"

int main(int argc, char* argv[]) {
   
    Game game;
    bool success = game.Initialize();
    if (success) {
        game.RunLoop();
    }
    game.Shutdown();
    
    return 0;
}
