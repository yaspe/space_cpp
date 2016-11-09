#pragma once

#include <cmath>

namespace NEngine {

    struct TPoint {
        TPoint() = default;
        TPoint(const TPoint&) = default;
        TPoint(double x, double y) {
            X = x;
            Y = y;
        }

        TPoint& operator += (const TPoint& other) {
            X += other.X;
            Y += other.Y;
            return *this;
        }

        double Straight() const {
            return sqrt(X*X + Y*Y);
        }

        double X = 0;
        double Y = 0;
    };

    TPoint operator / (const TPoint& p, int k);
    TPoint operator - (const TPoint& r, const TPoint& l);
    TPoint operator + (const TPoint& r, const TPoint& l);

}
