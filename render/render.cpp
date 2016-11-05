#include "render.h"
#include "texture_loader.h"

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

            SDL_RenderCopyEx(Renderer, TTextureLoader::GetGlobal().Load(objectPtr->GetPngTextureName(), Renderer), nullptr, &objRect, objectPtr->GetAngle(), nullptr, SDL_FLIP_NONE);
        }

        SDL_RenderPresent(Renderer);
    }

}
