#include <vector>
#include <chrono>

#include "../engine/engine.h"
#include "../render/render.h"
#include "../controller/controller.h"

static const std::chrono::milliseconds TICK_LIMIT = static_cast<std::chrono::milliseconds>(1000 / 36);
std::chrono::milliseconds GetTicks() {
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch());
}

int main() {

    // todo: move all objects creation and processing to specail engine class
    NEngine::TEngine engine;
    
    NRender::TRenderer renderer(engine);
    std::chrono::milliseconds lastTicks = GetTicks();

    bool running = true;
    while (running) {

        switch (NController::PollEvent()) {
            case NController::TEventType::Quite:
                running = false;
                break;
            case NController::TEventType::MainEngineOn:
                engine.GetShip().SetMainEngineStatus(true);
                break;
            case NController::TEventType::MainEngineOff:
                engine.GetShip().SetMainEngineStatus(false);
                break;
            case NController::TEventType::LeftEngineOn:
                engine.GetShip().SetLeftEngineStatus(true);
                break;
            case NController::TEventType::LeftEngineOff:
                engine.GetShip().SetLeftEngineStatus(false);
                break;
            case NController::TEventType::RightEngineOn:
                engine.GetShip().SetRightEngineStatus(true);
                break;
            case NController::TEventType::RightEngineOff:
                engine.GetShip().SetRightEngineStatus(false);
                break;
            case NController::TEventType::Shoot:
                engine.GetShip().Shoot();
                break;
            default:
                break;
        }

        if (GetTicks() - lastTicks < TICK_LIMIT)
            continue;

        engine.Process();
        renderer.Render();

        lastTicks = GetTicks();
    }

    return 0;
}