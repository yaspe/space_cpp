#pragma once

#include "object.h"
#include "planet.h"
#include "ship.h"
#include "background_star.h"
#include "sun.h"

#include <vector>

namespace NEngine {

    class TEngine {
    public:
        TEngine();

        void Process();
        TPoint CalcRelativePosition(const TObject& object) const;

        TPoint GetScreenSize() const;
        TPoint GetWorldSize() const;
        TPoint GetWorldCenter() const;
        double GetMinWorldBoundary() const;

        std::vector<TObject*> GetObjects(bool mapOnly=false);
        std::vector<const TObject*> GetConstObjects(bool mapOnly=false) const;
        TShip& GetShip();
        const TShip& GetConstShip() const;

    private:
        void ApplyGravity();
        void ApplyGravityToSheep(TShip& ship);

    private:
        std::vector<TPlanet> Planets;
        std::vector<TBackGroundStar> BackGroundStars;
        TShip Ship;
        std::vector<TShip> AiShips;
        TSun Sun;
    };

}