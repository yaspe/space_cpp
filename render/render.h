#pragma once

#include <vector>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace NEngine {
    class TObject;
}

namespace NRender {

    class TRenderer {
    public:
        TRenderer();
        void Render(const std::vector<NEngine::TObject*>&);

    private:
        SDL_Window* Window;
        SDL_Renderer* Renderer;
    };



}