#pragma once

#include "object.h"

namespace NEngine {

    class TShip : public TObject {
    public:
        TShip();

        std::string GetPngTextureName() const override;

        void SetMainEngineStatus(bool);
        void SetRightEngineStatus(bool);
        void SetLeftEngineStatus(bool);
    };
}
