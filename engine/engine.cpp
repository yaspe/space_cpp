#include "engine.h"

namespace NEngine {

    TEngine::TEngine(size_t planets) {
        for (size_t i = 0; i < planets; ++i) {
            TPlanet planet;
            planet.SetPosition((i + 1) * 200, (i + 1) * 200);
            Planets.emplace_back(std::move(planet));
        }

        Ship.SetPosition(100, 300);
    }

    void TEngine::Process() {
        for (auto& planet : Planets) {
            planet.Process();
        }

        for (auto& bullet : Ship.GetBullets()) {
            bullet.Process();
        }

        Ship.Process();
    }

    std::vector<TObject*> TEngine::GetObjects() {
        std::vector<TObject*> result;
        for (auto& planet : Planets) {
            result.push_back(&planet);
        }

        for (auto& bullet : Ship.GetBullets()) {
            result.push_back(&bullet);
        }

        result.push_back(&Ship);
        return result;
    }

    TShip& TEngine::GetShip() {
        return Ship;
    }

}
