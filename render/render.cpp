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

        DrawMap();

        SDL_RenderPresent(Renderer);
    }

    void TRenderer::DrawMap() {
        const size_t mapSize = 150;
        const int mapTopX = static_cast<int>(Engine.GetScreenSize().X - mapSize - 10);
        const int mapTopY = static_cast<int>(Engine.GetScreenSize().Y - mapSize - 10);
        const int objSize = 6;

        SDL_Rect border = {mapTopX, mapTopY, mapSize, mapSize};
        SDL_SetRenderDrawColor(Renderer, 100, 100, 100, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawRect(Renderer, &border);

        for (const auto objectPtr : Engine.GetConstObjects(true)) {
            SDL_Rect objRect;
            objRect.x = mapTopX + static_cast<int>(mapSize * objectPtr->GetPosition().X / Engine.GetWorldSize().X - objSize / 2);
            objRect.y = mapTopY + static_cast<int>(mapSize * objectPtr->GetPosition().Y / Engine.GetWorldSize().Y - objSize / 2);
            objRect.w = objSize;
            objRect.h = objSize;
            if (objectPtr == &Engine.GetConstShip()) {
                SDL_SetRenderDrawColor(Renderer, 10, 10, 255, SDL_ALPHA_OPAQUE);
            } else {
                const uint8_t color = static_cast<uint8_t>(objectPtr->GetSize() % 255);
                SDL_SetRenderDrawColor(Renderer, color, color, color, SDL_ALPHA_OPAQUE);
            }
            SDL_RenderFillRect(Renderer, &objRect);
        }
    }

}
