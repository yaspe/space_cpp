#pragma once

#include "object.h"

namespace NEngine {

    class TBackGroundStar : public TObject {
    public:
        TBackGroundStar();

        std::string GetPngTextureName() const override;

        void Process() override;
    private:
        std::string TextureName;
    };

}
