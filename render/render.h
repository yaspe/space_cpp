#pragma once

#include "../engine/engine.h"

#include <vector>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace NRender {

    class TRenderer {
    public:
        TRenderer(const NEngine::TEngine& engine);
        ~TRenderer();
        void Render();

    private:
        const NEngine::TEngine& Engine;
        SDL_Window* Window;
        SDL_Renderer* Renderer;
    };



}