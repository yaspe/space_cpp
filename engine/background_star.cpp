#include "background_star.h"

#include <cstdlib>

namespace NEngine {

    TBackGroundStar::TBackGroundStar() {
        TextureName = "bgstar" + std::to_string(1 + rand() % 2) + ".png";
        Size = static_cast<size_t>(2 + rand() % 5);
    }

    std::string TBackGroundStar::GetPngTextureName() const {
        return TextureName;
    }

    // тут нет смысла что-то вычислять
    void TBackGroundStar::Process() {
    }

}
