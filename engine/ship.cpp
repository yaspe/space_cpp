#include "ship.h"

#include <cmath>

static const double MAIN_ENGINE_POWER = 0.05; // pixels per time
static const double SIDE_ENGINE_POWER = 0.2; // degrees

static double DegreesToRadians(double degrees) {
    return M_PI * degrees / 180;
}

namespace NEngine {

    TShip::TShip() {
        Size = 48;
    }

    std::string TShip::GetPngTextureName() const {
        return "ship.png";
    }

    void TShip::SetMainEngineStatus(bool on) {
        if (on) {
            Acc.X = -sin(DegreesToRadians(Angle)) * MAIN_ENGINE_POWER;
            Acc.Y = cos(DegreesToRadians(Angle)) * MAIN_ENGINE_POWER;
        } else {
            Acc.X = 0;
            Acc.Y = 0;
        }
    }

    void TShip::SetLeftEngineStatus(bool on) {
        if (on) {
            AngleAcc = -0.5;
        } else {
            AngleAcc = 0;
        }
    }

    void TShip::SetRightEngineStatus(bool on) {
        if (on) {
            AngleAcc = 0.5;
        } else {
            AngleAcc = 0;
        }
    }

}
