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

    TPoint TEngine::CalcRelativePosition(const TObject& object) const {
        return object.GetPosition();
    }

    std::vector<const TObject*> TEngine::GetObjects() const {
        std::vector<const TObject*> result;
        for (const auto& planet : Planets) {
            result.push_back(&planet);
        }

        for (const auto& bullet : Ship.GetBullets()) {
            result.push_back(&bullet);
        }

        result.push_back(&Ship);
        return result;
    }

    TShip& TEngine::GetShip() {
        return Ship;
    }

}
