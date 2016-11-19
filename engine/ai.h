#pragma once

#include "ship.h"

#include <vector>

namespace NEngine {

    void ThinkThenDo(TShip& ship, const std::vector<TShip*>& targetShips);

}
