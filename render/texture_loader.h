#pragma once

#include <map>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_surface.h>

namespace NRender {

    class TTextureLoader {
    public:
        SDL_Texture* Load(const std::string& path, SDL_Renderer* renderer);
        static TTextureLoader& GetGlobal();

        ~TTextureLoader();

    private:
        TTextureLoader() = default;

    private:
        std::map<std::string, SDL_Texture*> Textures;

    };

}
