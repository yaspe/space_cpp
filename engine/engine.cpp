#include "engine.h"

#include <cstdlib>

namespace NEngine {

    static const size_t PLANETS_NUM = 10;
    static const size_t BG_STARS_NUM = 5000;

    TEngine::TEngine() {
        for (size_t i = 0; i < PLANETS_NUM; ++i) {
            TPlanet planet;
            planet.SetPosition((i + 1) * 200, (i + 1) * 200);
            Planets.emplace_back(std::move(planet));
        }

        for (size_t i = 0; i < BG_STARS_NUM; ++i) {
            TBackGroundStar star;
            star.SetPosition(rand() % static_cast<int>(GetWorldSize().X), rand() % static_cast<int>(GetWorldSize().Y));
            BackGroundStars.emplace_back(std::move(star));
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

    std::vector<const TObject*> TEngine::GetObjects() const {
        std::vector<const TObject*> result;

        for (const auto& star : BackGroundStars) {
            result.push_back(&star);
        }

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

    TPoint TEngine::GetScreenSize() const {
        return TPoint(800, 640);
    }

    TPoint TEngine::GetWorldSize() const {
        return TPoint(4000, 4000);
    }

    TPoint TEngine::CalcRelativePosition(const TObject& object) const {
        TPoint result = object.GetPosition() - Ship.GetPosition() + GetScreenSize() / 2;
        return result;
    }

}
