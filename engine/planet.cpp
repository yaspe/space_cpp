#include "planet.h"

namespace NEngine {

    TPlanet::TPlanet() {
        Size = 240;
    }

    std::string TPlanet::GetPngTextureName() const {
        return "planet.png";
    }

}