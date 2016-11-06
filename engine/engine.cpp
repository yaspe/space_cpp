#include "engine.h"

#include <cstdlib>

namespace NEngine {

    static const size_t PLANETS_NUM = 10;
    static const size_t BG_STARS_NUM = 5000;

    TEngine::TEngine() {
        for (size_t i = 0; i < PLANETS_NUM; ++i) {
            TPlanet planet;
            planet.SetPosition(rand() %static_cast<int>(GetWorldSize().X), (i + 1) * GetWorldSize().Y / PLANETS_NUM);
            planet.Speed.X = (10 - rand() % 20) / 10.0;
            Planets.emplace_back(std::move(planet));
        }

        for (size_t i = 0; i < BG_STARS_NUM; ++i) {
            TBackGroundStar star;
            star.SetPosition(rand() % static_cast<int>(GetWorldSize().X), rand() % static_cast<int>(GetWorldSize().Y));
            BackGroundStars.emplace_back(std::move(star));
        }

        Ship.SetPosition(500, 500);
    }

    void TEngine::Process() {
        for (auto& objectPtr : GetObjects()) {
            objectPtr->Process();
            if (objectPtr->GetPosition().X > GetWorldSize().X) {
                objectPtr->Position.X -= GetWorldSize().X;
            } else if (objectPtr->GetPosition().X < 0) {
                objectPtr->Position.X = GetWorldSize().X - objectPtr->Position.X;
            }
            if (objectPtr->GetPosition().Y > GetWorldSize().Y) {
                objectPtr->Position.Y -= GetWorldSize().Y;
            } else if (objectPtr->GetPosition().X < 0) {
                objectPtr->Position.Y = GetWorldSize().Y - objectPtr->Position.Y;
            }
        }
    }

    std::vector<TObject*> TEngine::GetObjects() {
        std::vector<TObject*> result;

        for (auto& star : BackGroundStars) {
            result.push_back(&star);
        }

        for (auto& planet : Planets) {
            result.push_back(&planet);
        }

        for (auto& bullet : Ship.GetBullets()) {
            result.push_back(&bullet);
        }

        result.push_back(&Ship);
        return result;
    }

    std::vector<const TObject*> TEngine::GetConstObjects() const {
        std::vector<const TObject*> result;
        for (auto& objectPtr : const_cast<TEngine*>(this)->GetObjects())
            result.push_back(objectPtr);
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
        if (result.X + object.Size > GetWorldSize().X) {
            result.X -= GetWorldSize().X;
        } else if (Ship.Position.X > GetWorldSize().X - GetScreenSize().X / 2 && object.Position.X < object.Size + GetScreenSize().X / 2) {
            result.X = GetWorldSize().X + object.Position.X - Ship.Position.X + GetScreenSize().X / 2;
        }

        if (result.Y + object.Size > GetWorldSize().Y) {
            result.Y -= GetWorldSize().Y;
        } else if (Ship.Position.Y > GetWorldSize().Y - GetScreenSize().Y / 2 && object.Position.Y < object.Size + GetScreenSize().Y / 2) {
            result.Y = GetWorldSize().Y + object.Position.Y - Ship.Position.Y + GetScreenSize().Y / 2;
        }

        return result;
    }

}
