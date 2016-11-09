#include "planet.h"

namespace NEngine {

    TPlanet::TPlanet() {
        Size = 240;
        Mass = 100;
    }

    std::string TPlanet::GetPngTextureName() const {
        return "planet.png";
    }

}