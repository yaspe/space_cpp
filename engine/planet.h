#pragma once

#include "object.h"

namespace NEngine {

    class TPlanet : public TObject {
    public:
        TPlanet();

        std::string GetPngTextureName() const override;
    };

}
