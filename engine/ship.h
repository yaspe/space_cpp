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

        std::vector<TBullet>& GetBullets() const;

    private:
        bool CanShoot() const;
        void ProcessEngines();

    private:
        const size_t TicksToReload = 50;
        size_t Ticks = 50;
        mutable std::vector<TBullet> Bullets;
        bool MainEngineStatus = false;
    };
}
