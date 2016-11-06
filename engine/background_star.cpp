#include "background_star.h"

#include <cstdlib>

namespace NEngine {

    TBackGroundStar::TBackGroundStar() {
        Size = static_cast<size_t>(2 + rand() % 5);
    }

    std::string TBackGroundStar::GetPngTextureName() const {
        return "bgstar.png";
    }

}
