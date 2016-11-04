#include "object.h"

namespace NEngine {

    void TObject::Process() {
        Speed += Acc;
        Position += Speed;
        AngleSpeed += AngleAcc;
        Angle += AngleSpeed;
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

    void TObject::SetPosition(double x, double y) {
        SetPosition(TPoint(x, y));
    }

    void TObject::SetPosition(const TPoint& point) {
        Position = point;
    }

}