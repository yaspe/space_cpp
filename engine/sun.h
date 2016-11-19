#pragma once

#include "object.h"

namespace NEngine {

    class TSun : public TObject {
    public:
        TSun();
        void Process() override;

        std::string GetPngTextureName() const override;
    };

}