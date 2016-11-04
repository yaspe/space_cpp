#include "controller.h"

#include <SDL2/SDL.h>

namespace NController {

    TEventType PollEvent() {

        SDL_Event event;
        if (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT: return TEventType::Quite;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_DOWN)
                        return TEventType::MainEngineOn;
                    if (event.key.keysym.sym == SDLK_LEFT)
                        return TEventType::LeftEngineOn;
                    if (event.key.keysym.sym == SDLK_RIGHT)
                        return TEventType::RightEngineOn;
                case SDL_KEYUP:
                    if (event.key.keysym.sym == SDLK_DOWN)
                        return TEventType::MainEngineOff;
                    if (event.key.keysym.sym == SDLK_LEFT)
                        return TEventType::LeftEngineOff;
                    if (event.key.keysym.sym == SDLK_RIGHT)
                        return TEventType::RightEngineOff;
                default: break;
            }
        }

            return TEventType::None;
    }

}