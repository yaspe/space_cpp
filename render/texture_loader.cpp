#include "texture_loader.h"

static SDL_Texture* LoadTexture(const std::string& path, SDL_Renderer* renderer) {
    //The final texture
    SDL_Texture* newTexture = nullptr;
    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == nullptr ) {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    } else {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if( newTexture == nullptr ) {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }
        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    } return newTexture;
}

namespace NRender {

    SDL_Texture* TTextureLoader::Load(const std::string& path, SDL_Renderer* renderer) {
        auto found = Textures.find(path);
        if (found != Textures.end())
            return found->second;

        auto newTexture = LoadTexture(path, renderer);
        Textures[path] = newTexture;
        return newTexture;
    }


    TTextureLoader& TTextureLoader::GetGlobal() {
        static TTextureLoader loader;
        return loader;
    }

}