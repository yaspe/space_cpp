#include "render.h"

#include "../engine/object.h"

namespace NRender {

    TRenderer::TRenderer() {
        SDL_Init(SDL_INIT_EVERYTHING);
        SDL_CreateWindowAndRenderer(800, 640, SDL_WINDOW_SHOWN, &Window, &Renderer);
    }

    void TRenderer::Render(const std::vector<NEngine::TObject*>& objects) {
        SDL_SetRenderDrawColor(Renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(Renderer);

        for (const auto objectPtr : objects) {
            SDL_Rect objRect ;
            objRect.x = static_cast<int>(objectPtr->GetPosition().X - objectPtr->GetSize() / 2);
            objRect.y = static_cast<int>(objectPtr->GetPosition().Y - objectPtr->GetSize() / 2);
            objRect.w = static_cast<int>(objectPtr->GetSize());
            objRect.h = static_cast<int>(objectPtr->GetSize());

            SDL_RenderCopyEx(Renderer, LoadTexture(objectPtr->GetPngTextureName()), nullptr, &objRect, objectPtr->GetAngle(), nullptr, SDL_FLIP_NONE);
        }

        SDL_RenderPresent(Renderer);
    }

    SDL_Texture* TRenderer::LoadTexture(const std::string& path) const {
        //The final texture
        SDL_Texture* newTexture = nullptr;
        //Load image at specified path
        SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
        if( loadedSurface == nullptr ) {
            printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
        } else {
            //Create texture from surface pixels
            newTexture = SDL_CreateTextureFromSurface( Renderer, loadedSurface );
            if( newTexture == nullptr ) {
                printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
            }
            //Get rid of old loaded surface
            SDL_FreeSurface( loadedSurface );
        } return newTexture;
    }

}
