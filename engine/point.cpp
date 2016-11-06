#include "point.h"

namespace NEngine {

    TPoint operator / (const TPoint& p, int k) {
        return TPoint(p.X / k, p.Y / k);
    }

    TPoint operator - (const TPoint& r, const TPoint& l) {
        return TPoint(r.X - l.X, r.Y - l.Y);
    }

    TPoint operator + (const TPoint& r, const TPoint& l) {
        return TPoint(r.X + l.X, r.Y + l.Y);
    }

}
