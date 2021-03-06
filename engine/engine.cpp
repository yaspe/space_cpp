#include "engine.h"
#include "ai.h"

#include <cstdlib>
#include <iostream>

namespace NEngine {

    static const size_t PLANETS_NUM = 3;
    static const size_t BG_STARS_NUM = 5000;
    static const double GRAVITY = 70.0;
    static const TPoint WORLD_SIZE = TPoint(4000, 4000);
    static const TPoint SCREEN_SIZE = TPoint(800, 640);
    static const double PLANET_MAX_ORBIT_SPEED = 0.001;
    static const size_t PLANET_MARGIN = 100;
    static const size_t FRIENDLY_SHIPS_NUM = 0;
    static const size_t ENEMY_SHIPS_NUM = 3;

    TEngine::TEngine() {
        Sun.SetPosition(GetWorldCenter());

        for (size_t i = 0; i < PLANETS_NUM; ++i) {
            TPlanet planet(Sun.Position);
            const double planetShift = (GetMinWorldBoundary() / 2 - Sun.Size - PLANET_MARGIN) / PLANETS_NUM;
            planet.SetOrbitRadius(planet.Size + planetShift * i + Sun.Size + PLANET_MARGIN);
            planet.SetOrbitSpeed(PLANET_MAX_ORBIT_SPEED - rand() % static_cast<int>(20000 * PLANET_MAX_ORBIT_SPEED) / 10000.0);
            planet.SetOrbitAngle(rand() % 360);
            Planets.emplace_back(std::move(planet));
        }

        for (size_t i = 0; i < BG_STARS_NUM; ++i) {
            TBackGroundStar star;
            star.SetPosition(rand() % static_cast<int>(GetWorldSize().X), rand() % static_cast<int>(GetWorldSize().Y));
            BackGroundStars.emplace_back(std::move(star));
        }

        for (size_t i = 0; i < FRIENDLY_SHIPS_NUM; ++i) {
            TShip ship;
            ship.SetPosition(rand() % static_cast<int>(GetWorldSize().X), (i + 1) * GetWorldSize().Y / PLANETS_NUM);
            FriendlyShips.emplace_back(std::move(ship));
        }

        for (size_t i = 0; i < ENEMY_SHIPS_NUM; ++i) {
            TShip ship;
            ship.SetPosition(rand() % static_cast<int>(GetWorldSize().X), (i + 1) * GetWorldSize().Y / PLANETS_NUM);
            EnemyShips.emplace_back(std::move(ship));
        }

        Ship.SetPosition(3500, 2000);
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
            } else if (objectPtr->GetPosition().Y < 0) {
                objectPtr->Position.Y = GetWorldSize().Y - objectPtr->Position.Y;
            }
        }
        ApplyGravity();
        ApplyAi();
        CheckCollisions();
    }

    void TEngine::CheckCollisions() {
        for (auto& bullet : Ship.GetBullets())
            for (auto& enemy: EnemyShips)
                if ((bullet.Position - enemy.Position).Straight() < enemy.Size / 2) {
                    bullet.Expire();
                    enemy.Kill();
                }

    }

    static TPoint ApplyGravityImpl(const TObject& dealer, TObject& object, const TPoint& planetPos, const TPoint& objPos) {
        auto distance = planetPos - objPos;
        auto totalDistance = std::max(static_cast<size_t>(distance.Straight()), dealer.GetSize());
        auto totalForce = GRAVITY * dealer.GetMass() / (totalDistance * totalDistance);
        TPoint force(distance.X * totalForce / totalDistance, distance.Y * totalForce / totalDistance);
        return force;
    }

    void TEngine::ApplyGravityToSheep(TShip& ship) {
        const TPoint shipPos = CalcRelativePosition(ship);
        const TPoint sunPos = CalcRelativePosition(Sun);
        for (auto& planet : Planets) {
            const TPoint planetPos = CalcRelativePosition(planet);
            ship.Speed += ApplyGravityImpl(planet, ship, planetPos, shipPos);
            for (auto& bullet : ship.GetBullets())
                bullet.Speed += ApplyGravityImpl(planet, bullet, planetPos, CalcRelativePosition(bullet));
        }

        ship.Speed += ApplyGravityImpl(Sun, ship, sunPos, shipPos);
    }

    void TEngine::ApplyGravity() {
        ApplyGravityToSheep(Ship);
        for (auto& aiShip : FriendlyShips)
            ApplyGravityToSheep(aiShip);
        for (auto& aiShip : EnemyShips)
            ApplyGravityToSheep(aiShip);
    }

    std::vector<TObject*> TEngine::GetObjects(bool mapOnly) {
        std::vector<TObject*> result;

        if (!mapOnly)
            for (auto& star : BackGroundStars) {
                result.push_back(&star);
            }

        result.push_back(&Sun);

        for (auto& planet : Planets) {
            result.push_back(&planet);
        }

        if (!mapOnly)
            for (auto& bullet : Ship.GetBullets()) {
                result.push_back(&bullet);
            }

        for (auto& ship : FriendlyShips) {
            result.push_back(&ship);
            if (!mapOnly)
                for (auto& bullet : ship.GetBullets()) {
                    result.push_back(&bullet);
                }
        }

        for (auto& ship : EnemyShips) {
            result.push_back(&ship);
            if (!mapOnly)
                for (auto& bullet : ship.GetBullets()) {
                    result.push_back(&bullet);
                }
        }

        result.push_back(&Ship);
        return result;
    }

    void TEngine::ApplyAi() {
        std::vector<TShip*> targetShips;
        targetShips.push_back(&Ship);
        for (auto& ship : EnemyShips) {
            ThinkThenDo(ship, targetShips);
        }
    }

    std::vector<const TObject*> TEngine::GetConstObjects(bool mapOnly) const {
        // todo: тут плохо сделано с тз производительности
        // todo: можно бы переделать, но не критично, пока не жмет
        std::vector<const TObject*> result;
        for (auto& objectPtr : const_cast<TEngine*>(this)->GetObjects(mapOnly))
            result.push_back(objectPtr);
        return result;
    }

    TShip& TEngine::GetShip() {
        return Ship;
    }

    const TShip& TEngine::GetConstShip() const {
        return Ship;
    }

    TPoint TEngine::GetScreenSize() const {
        return SCREEN_SIZE;
    }

    TPoint TEngine::GetWorldSize() const {
        return WORLD_SIZE;
    }

    TPoint TEngine::GetWorldCenter() const {
        TPoint center = TPoint(GetWorldSize().X / 2, GetWorldSize().Y / 2);
        return center;
    }

    double TEngine::GetMinWorldBoundary() const {
        return std::min(GetWorldSize().Y, GetWorldSize().X);
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
