#include "render.h"
#include "texture_loader.h"

namespace NRender {

    TRenderer::TRenderer(const NEngine::TEngine& engine)
        : Engine(engine)
    {
        SDL_Init(SDL_INIT_EVERYTHING);
        SDL_CreateWindowAndRenderer(
                static_cast<int>(Engine.GetScreenSize().X),
                static_cast<int>(Engine.GetScreenSize().Y),
                SDL_WINDOW_SHOWN, &Window,
                &Renderer);
    }

    TRenderer::~TRenderer() {
        SDL_DestroyRenderer(Renderer);
        SDL_DestroyWindow(Window);
    }

    void TRenderer::Render() {
        SDL_SetRenderDrawColor(Renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(Renderer);

        for (const auto objectPtr : Engine.GetConstObjects()) {
            const NEngine::TPoint relativePos = Engine.CalcRelativePosition(*objectPtr);
            if (relativePos.X + objectPtr->GetSize() < 0
                || relativePos.X - objectPtr->GetSize() > Engine.GetScreenSize().X
                || relativePos.Y + objectPtr->GetSize() < 0
                || relativePos.Y - objectPtr->GetSize() > Engine.GetScreenSize().Y)
                continue;

            SDL_Rect objRect;
            objRect.x = static_cast<int>(relativePos.X - objectPtr->GetSize() / 2);
            objRect.y = static_cast<int>(relativePos.Y - objectPtr->GetSize() / 2);
            objRect.w = static_cast<int>(objectPtr->GetSize());
            objRect.h = static_cast<int>(objectPtr->GetSize());

            SDL_RenderCopyEx(Renderer, TTextureLoader::GetGlobal().Load(objectPtr->GetPngTextureName(), Renderer), nullptr, &objRect, objectPtr->GetAngle(), nullptr, SDL_FLIP_NONE);
        }

        SDL_RenderPresent(Renderer);
    }

}
