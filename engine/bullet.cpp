#include "bullet.h"

namespace NEngine {

    TBullet::TBullet() {
        Size = 8;
    }

    std::string TBullet::GetPngTextureName() const {
        return "bullet.png";
    }

    void TBullet::Process() {
        TObject::Process();
        if (!Expired()) {
            Ticks += 1;
        }
    }

    void TBullet::Expire() {
        Ticks = TicksToExpire;
    }

    bool TBullet::Expired() const {
        return Ticks >= TicksToExpire;
    }

}