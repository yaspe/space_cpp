#include "object.h"

static const double MAX_SPEED = 10;

namespace NEngine {

    void TObject::Process() {
        auto newSpeed = Speed + Acc;
        if (newSpeed.Straight() < MAX_SPEED || newSpeed.Straight() < Speed.Straight())
            Speed += Acc;
        Position += Speed;
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
        return Angle;
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