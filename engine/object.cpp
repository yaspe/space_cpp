#include "object.h"

#include <cstdlib>

static const double MAX_SPEED = 10;
static const double MAX_ANGLE_SPEED = 15;

namespace NEngine {

    void TObject::Process() {
        auto newSpeed = Speed + Acc;
        if (newSpeed.Straight() < MAX_SPEED || newSpeed.Straight() < Speed.Straight())
            Speed += Acc;
        Position += Speed;

        auto newAngleSpeed = AngleSpeed + AngleAcc;
        if (abs(static_cast<int>(newAngleSpeed)) < MAX_ANGLE_SPEED || abs(static_cast<int>(newAngleSpeed)) < abs(static_cast<int>(AngleSpeed)))
            AngleSpeed += AngleAcc;

        Angle += AngleSpeed;
        AngleSpeed *= 0.99;
    }

    bool TObject::IsGravityDealer() const {
        return Mass > 0;
    }

    const TPoint& TObject::GetPosition() const {
        return Position;
    }

    const TPoint& TObject::GetSpeed() const {
        return Speed;
    }

    const TPoint& TObject::GetAcc() const {
        return Acc;
    }

    double TObject::GetAngle() const {
        return static_cast<int>(Angle) % 360;
    }

    size_t TObject::GetSize() const {
        return Size;
    }

    size_t TObject::GetMass() const {
        return Mass;
    }

    void TObject::SetPosition(double x, double y) {
        SetPosition(TPoint(x, y));
    }

    void TObject::SetPosition(const TPoint& point) {
        Position = point;
    }

}