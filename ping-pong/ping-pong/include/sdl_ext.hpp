#pragma once
#include <SDL2/SDL.h>

namespace SDL_EXT {

    void DrawFilledCircle(SDL_Renderer* renderer, int centerX, int centerY, int radius) {
        for (int w = -radius; w <= radius; w++) {
            for (int h = -radius; h <= radius; h++) {
                int dx = radius - w;
                int dy = radius - h;
                if ((dx * dx + dy * dy) <= (radius * radius)) {
                    SDL_RenderDrawPoint(renderer, centerX + dx, centerY + dy);
                }
            }
        }
    }

}


