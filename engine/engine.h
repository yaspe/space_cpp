#pragma once

#include "object.h"
#include "planet.h"
#include "ship.h"
#include "background_star.h"

#include <vector>

namespace NEngine {

    class TEngine {
    public:
        TEngine();

        void Process();
        TPoint CalcRelativePosition(const TObject& object) const;

        TPoint GetScreenSize() const;
        TPoint GetWorldSize() const;
        std::vector<const TObject*> GetObjects() const;
        TShip& GetShip();

    private:
        std::vector<TPlanet> Planets;
        std::vector<TBackGroundStar> BackGroundStars;
        TShip Ship;
    };

}