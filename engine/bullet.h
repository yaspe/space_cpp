#pragma once

#include "object.h"

namespace NEngine {

    class TBullet : public TObject {
        friend class TShip;
    public:
        TBullet();

        std::string GetPngTextureName() const override;

        void Process() override;

        bool Expired() const;

    private:
        size_t Ticks = 0;
        const size_t TicksToExpire = 500;
    };

}
