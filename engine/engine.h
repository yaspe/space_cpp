#pragma once

#include "object.h"
#include "planet.h"
#include "ship.h"

#include <vector>

namespace NEngine {

    class TEngine {
    public:
        TEngine(size_t planets);

        void Process();
        std::vector<TObject*> GetObjects();
        TShip& GetShip();

    private:
        std::vector<TPlanet> Planets;
        TShip Ship;
    };

}