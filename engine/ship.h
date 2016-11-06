#pragma once

#include "object.h"
#include "bullet.h"

#include <vector>

namespace NEngine {

    class TShip : public TObject {
    public:
        TShip();

        std::string GetPngTextureName() const override;

        void Process() override;

        void SetMainEngineStatus(bool);
        void SetRightEngineStatus(bool);
        void SetLeftEngineStatus(bool);

        void Shoot();

        std::vector<TBullet>& GetBullets();

    private:
        bool CanShoot() const;

    private:
        const size_t TicksToReload = 50;
        size_t Ticks = 50;
        std::vector<TBullet> Bullets;
    };
}
