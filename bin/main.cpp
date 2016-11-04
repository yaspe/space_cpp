#include <vector>
#include <chrono>

#include "../engine/object.h"
#include "../engine/ship.h"
#include "../engine/planet.h"
#include "../render/render.h"
#include "../controller/controller.h"

static const std::chrono::milliseconds TICK_LIMIT = static_cast<std::chrono::milliseconds>(1000 / 36);
std::chrono::milliseconds GetTicks() {
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch());
}

int main() {

    // todo: move all objects creation and processing to specail engine class
    NEngine::TShip ship;
    NEngine::TPlanet planet;

    ship.SetPosition(100, 100);
    planet.SetPosition(400, 400);

    std::vector<NEngine::TObject*> objects = {&planet, &ship};
    NRender::TRenderer renderer;
    std::chrono::milliseconds lastTicks = GetTicks();

    bool running = true;
    while (running) {

        switch (NController::PollEvent()) {
            case NController::TEventType::Quite:
                running = false;
                break;
            case NController::TEventType::MainEngineOn:
                ship.SetMainEngineStatus(true);
                break;
            case NController::TEventType::MainEngineOff:
                ship.SetMainEngineStatus(false);
                break;
            case NController::TEventType::LeftEngineOn:
                ship.SetLeftEngineStatus(true);
                break;
            case NController::TEventType::LeftEngineOff:
                ship.SetLeftEngineStatus(false);
                break;
            case NController::TEventType::RightEngineOn:
                ship.SetRightEngineStatus(true);
                break;
            case NController::TEventType::RightEngineOff:
                ship.SetRightEngineStatus(false);
                break;
            default:
                break;
        }

        if (GetTicks() - lastTicks < TICK_LIMIT)
            continue;

        for (auto objectPtr : objects) {
            objectPtr->Process();
        }
        renderer.Render(objects);

        lastTicks = GetTicks();
    }

    return 0;
}