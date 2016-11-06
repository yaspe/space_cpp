#include "ship.h"

#include <cmath>

static const double MAIN_ENGINE_POWER = 0.05; // pixels per time
static const double SIDE_ENGINE_POWER = 0.35; // degrees
static const double BULLET_SPEED = 5;

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

    void TShip::Process() {
        TObject::Process();
        if (!CanShoot())
            Ticks += 1;
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
            AngleAcc = -SIDE_ENGINE_POWER;
        } else {
            AngleAcc = 0;
        }
    }

    void TShip::SetRightEngineStatus(bool on) {
        if (on) {
            AngleAcc = SIDE_ENGINE_POWER;
        } else {
            AngleAcc = 0;
        }
    }

    void TShip::Shoot() {
        if (!CanShoot())
            return;

        Ticks = 0;
        TBullet bullet;
        bullet.SetPosition(Position);
        bullet.Speed.X = Speed.X - sin(DegreesToRadians(Angle)) * BULLET_SPEED;
        bullet.Speed.Y = Speed.Y + cos(DegreesToRadians(Angle)) * BULLET_SPEED;
        Bullets.emplace_back(std::move(bullet));
    }

    std::vector<TBullet>& TShip::GetBullets() const {
        std::vector<TBullet> goodBullets;
        for (auto& bullet : Bullets) {
            if (!bullet.Expired()) {
                goodBullets.emplace_back(std::move(bullet));
            }
        }
        std::swap(Bullets, goodBullets);
        return Bullets;
    }

    bool TShip::CanShoot() const {
        return Ticks > TicksToReload;
    }

}
